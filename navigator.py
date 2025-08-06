#!/usr/bin/env python3
import os
import curses
import subprocess
import json

CONFIG_FILE = os.path.expanduser("~/.navigator_config.json")
BASE_REPO = os.path.expanduser("~/Ismail_Gilani_42_Firenze")

def load_config():
    if os.path.exists(CONFIG_FILE):
        with open(CONFIG_FILE, 'r') as f:
            return json.load(f)
    return {
        "current_project": None,
        "project_map": {},
        "last_opened_in_vscode": None
    }

def save_config(config):
    with open(CONFIG_FILE, 'w') as f:
        json.dump(config, f, indent=4)

def is_image_or_pdf(file):
    return file.lower().endswith((".png", ".jpg", ".jpeg", ".gif", ".bmp", ".pdf"))

def open_entry(path):
    if os.path.isdir(path):
        return "open_dir"
    elif is_image_or_pdf(path):
        subprocess.Popen(["xdg-open", path])
    else:
        subprocess.Popen(["code", path])
    return None

def open_in_terminal(path):
    subprocess.Popen(["gnome-terminal", "--working-directory", path])

def open_in_vscode(path):
    subprocess.Popen(["code", path])

def get_git_status():
    """Get git status of the BASE_REPO"""
    try:
        # Check if it's a git repository
        result = subprocess.run(["git", "rev-parse", "--is-inside-work-tree"], 
                              cwd=BASE_REPO, capture_output=True, text=True)
        if result.returncode != 0:
            return None, "Not a git repository"
        
        # Fetch remote to get latest info (quietly)
        # subprocess.run(["git", "fetch"], cwd=BASE_REPO, capture_output=True, text=True)
        
        # Get status of staged/unstaged files
        result = subprocess.run(["git", "status", "--porcelain"], 
                              cwd=BASE_REPO, capture_output=True, text=True)
        if result.returncode != 0:
            return None, "Git status failed"
        
        modified_files = result.stdout.strip().split('\n') if result.stdout.strip() else []
        
        # Check for unpushed commits (local ahead of remote)
        result = subprocess.run(["git", "log", "@{u}..HEAD", "--oneline"], 
                              cwd=BASE_REPO, capture_output=True, text=True)
        unpushed_commits = result.stdout.strip().split('\n') if result.stdout.strip() else []
        
        # Check for unpulled commits (remote ahead of local) - THIS IS THE KEY PART
        result = subprocess.run(["git", "log", "HEAD..@{u}", "--oneline"], 
                              cwd=BASE_REPO, capture_output=True, text=True)
        unpulled_commits = result.stdout.strip().split('\n') if result.stdout.strip() else []
        
        # Determine status
        has_modified = bool(modified_files and modified_files != [''])
        has_unpushed = bool(unpushed_commits and unpushed_commits != [''])
        has_unpulled = bool(unpulled_commits and unpulled_commits != [''])
        
        if has_unpulled:
            # Remote is ahead - NEED TO PULL FIRST!
            return "need_pull", {
                "modified": modified_files, 
                "unpushed": unpushed_commits,
                "unpulled": unpulled_commits
            }
        elif has_modified and has_unpushed:
            return "both", {"modified": modified_files, "unpushed": unpushed_commits, "unpulled": []}
        elif has_modified:
            return "modified", {"modified": modified_files, "unpushed": [], "unpulled": []}
        elif has_unpushed:
            return "unpushed", {"modified": [], "unpushed": unpushed_commits, "unpulled": []}
        else:
            return "clean", "All changes pushed"
            
    except Exception as e:
        return None, f"Git error: {str(e)}"

def show_git_status_screen(stdscr, status_type, status_data):
    """Show git status details and allow commit/push"""
    while True:
        # Get fresh status data
        current_status_type, current_status_data = get_git_status()
        
        # If status changed to clean, return to main menu
        if current_status_type == "clean" or current_status_type is None:
            return
            
        # Use current status for display
        display_type = current_status_type
        display_data = current_status_data
        
        stdscr.clear()
        
        if display_type == "modified":
            stdscr.addstr(0, 2, "🔴 Git Status - Modified Files")
        elif display_type == "unpushed":
            stdscr.addstr(0, 2, "🟡 Git Status - Unpushed Commits")
        elif display_type == "need_pull":
            stdscr.addstr(0, 2, "🚨 Git Status - NEED TO PULL FIRST!", curses.color_pair(1))
        else:  # both
            stdscr.addstr(0, 2, "🔴 Git Status - Modified Files & Unpushed Commits")
            
        stdscr.addstr(1, 2, "-" * (curses.COLS - 4))
        
        y = 3
        if display_data["unpulled"]:
            stdscr.addstr(y, 2, "⚠️ Remote commits to pull:", curses.color_pair(1))
            y += 1
            for commit in display_data["unpulled"][:5]:  # Show max 5 commits
                if y < curses.LINES - 4 and commit.strip():
                    stdscr.addstr(y, 4, f"• {commit}", curses.color_pair(1))
                    y += 1
            y += 1
            
        if display_data["modified"]:
            stdscr.addstr(y, 2, "Modified files:")
            y += 1
            for file in display_data["modified"][:10]:  # Show max 10 files
                if y < curses.LINES - 4 and file.strip():
                    stdscr.addstr(y, 4, f"• {file}")
                    y += 1
            y += 1
            
        if display_data["unpushed"]:
            stdscr.addstr(y, 2, "Unpushed commits:")
            y += 1
            for commit in display_data["unpushed"][:5]:  # Show max 5 commits
                if y < curses.LINES - 4 and commit.strip():
                    stdscr.addstr(y, 4, f"• {commit}")
                    y += 1
        
        # Key help at bottom - different options based on status
        if curses.LINES > 2:
            if display_type == "modified":
                stdscr.addstr(curses.LINES - 2, 2, "c:Commit&Push | r:Refresh | Backspace:Back")
            elif display_type == "unpushed":
                stdscr.addstr(curses.LINES - 2, 2, "p:Push | r:Refresh | Backspace:Back")
            elif display_type == "need_pull":
                stdscr.addstr(curses.LINES - 2, 2, "l:Pull | r:Refresh | Backspace:Back", curses.color_pair(1))
            else:  # both
                stdscr.addstr(curses.LINES - 2, 2, "c:Commit&Push | p:Push Only | r:Refresh | Backspace:Back")
        
        key = stdscr.getch()
        if key == curses.KEY_BACKSPACE or key == 127:
            return
        elif key == ord('c') and display_type not in ["unpushed", "need_pull"]:
            do_git_commit_push(stdscr)
            # Continue the loop to refresh status after commit/push
        elif key == ord('p') and display_type != "need_pull":
            do_git_push_only(stdscr)
            # Continue the loop to refresh status after push
        elif key == ord('l') and display_type == "need_pull":
            do_git_pull(stdscr)
            # Continue the loop to refresh status after pull
        elif key == ord('r'):
            # Just continue the loop - it will refresh at the start
            continue

def do_git_push_only(stdscr):
    """Push unpushed commits to remote"""
    stdscr.clear()
    stdscr.addstr(0, 2, "🚀 Pushing to remote...")
    stdscr.refresh()
    
    try:
        # Push to origin
        result = subprocess.run(["git", "push", "origin", "HEAD"], 
                              cwd=BASE_REPO, capture_output=True, text=True)
        
        stdscr.clear()
        if result.returncode == 0:
            stdscr.addstr(0, 2, "✅ Push successful!", curses.color_pair(2))
            stdscr.addstr(2, 2, "Changes pushed to remote repository.")
        else:
            stdscr.addstr(0, 2, "❌ Push failed!", curses.color_pair(1))
            stdscr.addstr(2, 2, "Error:")
            lines = result.stderr.split('\n')
            for i, line in enumerate(lines[:5]):  # Show first 5 lines of error
                if line.strip() and 3 + i < curses.LINES - 2:
                    stdscr.addstr(3 + i, 4, line[:curses.COLS - 6])
                    
        stdscr.addstr(curses.LINES - 2, 2, "Press any key to continue...")
        stdscr.getch()
        
    except Exception as e:
        stdscr.clear()
        stdscr.addstr(0, 2, f"❌ Error: {str(e)}", curses.color_pair(1))
        stdscr.addstr(curses.LINES - 2, 2, "Press any key to continue...")
        stdscr.getch()

def do_git_pull(stdscr):
    """Pull changes from remote repository"""
    stdscr.clear()
    stdscr.addstr(0, 2, "⬇️ Pulling changes from remote...")
    stdscr.refresh()
    
    try:
        # Pull from origin
        result = subprocess.run(["git", "pull"], 
                              cwd=BASE_REPO, capture_output=True, text=True)
        
        stdscr.clear()
        if result.returncode == 0:
            stdscr.addstr(0, 2, "✅ Pull successful!", curses.color_pair(2))
            stdscr.addstr(2, 2, "Remote changes pulled successfully.")
            if result.stdout:
                stdscr.addstr(4, 2, "Details:")
                lines = result.stdout.split('\n')
                for i, line in enumerate(lines[:3]):
                    if line.strip() and 5 + i < curses.LINES - 2:
                        stdscr.addstr(5 + i, 4, line[:curses.COLS - 6])
        else:
            stdscr.addstr(0, 2, "❌ Pull failed!", curses.color_pair(1))
            stdscr.addstr(2, 2, "Error:")
            lines = result.stderr.split('\n')
            for i, line in enumerate(lines[:5]):
                if line.strip() and 3 + i < curses.LINES - 2:
                    stdscr.addstr(3 + i, 4, line[:curses.COLS - 6])
                    
        stdscr.addstr(curses.LINES - 2, 2, "Press any key to continue...")
        stdscr.getch()
        
    except Exception as e:
        stdscr.clear()
        stdscr.addstr(0, 2, f"❌ Error: {str(e)}", curses.color_pair(1))
        stdscr.addstr(curses.LINES - 2, 2, "Press any key to continue...")
        stdscr.getch()

def do_git_commit_push(stdscr):
    """Commit changes and push to remote"""
    # Get commit message
    commit_msg = prompt_user_input(stdscr, "Commit message: ")
    if not commit_msg:
        return
    
    stdscr.clear()
    stdscr.addstr(0, 2, "📝 Committing changes...")
    stdscr.refresh()
    
    try:
        # Add all changes
        subprocess.run(["git", "add", "-A"], cwd=BASE_REPO, check=True)
        
        # Commit changes
        result = subprocess.run(["git", "commit", "-m", commit_msg], 
                              cwd=BASE_REPO, capture_output=True, text=True)
        
        if result.returncode != 0:
            stdscr.clear()
            stdscr.addstr(0, 2, "❌ Commit failed!", curses.color_pair(1))
            stdscr.addstr(2, 2, "Error:")
            lines = result.stderr.split('\n')
            for i, line in enumerate(lines[:5]):
                if line.strip() and 3 + i < curses.LINES - 2:
                    stdscr.addstr(3 + i, 4, line[:curses.COLS - 6])
            stdscr.addstr(curses.LINES - 2, 2, "Press any key to continue...")
            stdscr.getch()
            return
        
        # Now try to push
        stdscr.clear()
        stdscr.addstr(0, 2, "📝 Committed! 🚀 Now pushing...")
        stdscr.refresh()
        
        push_result = subprocess.run(["git", "push", "origin", "HEAD"], 
                                   cwd=BASE_REPO, capture_output=True, text=True)
        
        stdscr.clear()
        if push_result.returncode == 0:
            stdscr.addstr(0, 2, "✅ Commit & Push successful!", curses.color_pair(2))
            stdscr.addstr(2, 2, "Changes committed and pushed to remote.")
        else:
            stdscr.addstr(0, 2, "⚠️ Committed but push failed!", curses.color_pair(3))
            stdscr.addstr(2, 2, "Changes committed locally but not pushed to remote.")
            stdscr.addstr(3, 2, "You can retry push from Git status menu.")
            stdscr.addstr(5, 2, "Push error:")
            lines = push_result.stderr.split('\n')
            for i, line in enumerate(lines[:3]):
                if line.strip() and 6 + i < curses.LINES - 2:
                    stdscr.addstr(6 + i, 4, line[:curses.COLS - 6])
                    
        stdscr.addstr(curses.LINES - 2, 2, "Press any key to continue...")
        stdscr.getch()
        
    except Exception as e:
        stdscr.clear()
        stdscr.addstr(0, 2, f"❌ Error: {str(e)}", curses.color_pair(1))
        stdscr.addstr(curses.LINES - 2, 2, "Press any key to continue...")
        stdscr.getch()

def list_entries(path):
    try:
        with os.scandir(path) as it:
            entries = [(entry.name, entry.is_dir()) for entry in it if entry.name != ".git"]
        entries.sort(key=lambda e: (not e[1], e[0].lower()))  # Dir first, then alpha
        return entries
    except FileNotFoundError:
        return []

def prompt_user_input(stdscr, prompt):
    curses.curs_set(1)  # Show cursor
    stdscr.clear()
    stdscr.addstr(0, 0, prompt + " ")
    
    # Add ESC help at bottom
    if curses.LINES > 1:
        stdscr.addstr(curses.LINES - 1, 2, "Esc:Annulla")
    
    stdscr.refresh()
    
    # Position cursor after prompt
    stdscr.move(0, len(prompt) + 1)
    
    user_input = ""
    cursor_pos = len(prompt) + 1
    
    while True:
        key = stdscr.getch()
        if key == 27:  # ESC - ONLY here
            curses.curs_set(0)
            return None
        elif key in [10, 13]:  # ENTER
            break
        elif key in [curses.KEY_BACKSPACE, 127, 8]:  # Backspace
            if user_input:
                user_input = user_input[:-1]
                cursor_pos -= 1
                # Clear the character
                stdscr.move(0, cursor_pos)
                stdscr.delch(0, cursor_pos)
                stdscr.move(0, cursor_pos)
        elif 32 <= key <= 126:  # Printable characters
            char = chr(key)
            user_input += char
            stdscr.addch(0, cursor_pos, char)
            cursor_pos += 1
        stdscr.refresh()
    
    curses.curs_set(0)
    return user_input

def format_path_display(path):
    base = BASE_REPO + "/"
    return path.replace(base, "") if path.startswith(base) else path

def format_path_short(path):
    """Format path to show only last 2 components"""
    parts = path.rstrip('/').split('/')
    if len(parts) >= 2:
        return '/'.join(parts[-2:])
    return parts[-1] if parts else path

def manage_projects_menu(stdscr, config):
    """Show project management menu"""
    selection = 0
    
    while True:
        stdscr.clear()
        
        # Show current active project at top
        current_project = config.get("current_project")
        stdscr.addstr(0, 2, "🛠️ Gestione Progetti")
        stdscr.addstr(1, 2, "-" * (curses.COLS - 4))
        
        if current_project:
            stdscr.addstr(2, 2, f"📋 Progetto attivo: {current_project}", curses.color_pair(2))
        else:
            stdscr.addstr(2, 2, "📋 Progetto attivo: Nessuno", curses.color_pair(3))
        
        stdscr.addstr(3, 2, "-" * (curses.COLS - 4))
        
        menu_items = [
            "🗂️ Aggiungi milestone",
            "➕ Aggiungi nuovo progetto",
            "📝 Modifica progetto esistente",
            "🗑️ Elimina progetto",
            "🔄 Seleziona progetto attivo",
            "📋 Lista tutti i progetti"
        ]
        
        # Display menu items
        for idx, item in enumerate(menu_items):
            y_pos = 5 + idx
            if y_pos < curses.LINES - 2:
                highlight = curses.A_REVERSE if idx == selection else curses.A_NORMAL
                stdscr.addstr(y_pos, 3, item, highlight)
        
        # Key help at bottom
        if curses.LINES > 1:
            stdscr.addstr(curses.LINES - 1, 2, "↑↓:Muovi | Invio:Seleziona | Backspace:Torna indietro")
        
        key = stdscr.getch()
        if key == curses.KEY_BACKSPACE or key == 127:
            return
        elif key == curses.KEY_UP and selection > 0:
            selection -= 1
        elif key == curses.KEY_DOWN and selection < len(menu_items) - 1:
            selection += 1
        elif key in [10, 13]:  # ENTER
            if selection == 0:  # Add milestone
                add_milestone(stdscr, config)
            elif selection == 1:  # Add project
                add_new_project(stdscr, config)
            elif selection == 2:  # Edit project
                edit_project(stdscr, config)
            elif selection == 3:  # Delete project
                delete_project(stdscr, config)
            elif selection == 4:  # Select active project
                select_active_project(stdscr, config)
            elif selection == 5:  # List projects
                list_all_projects(stdscr, config)
        
        stdscr.refresh()

def create_project_in_folder(stdscr, config, folder_path):
    """Create a project in the specified folder path"""
    # Ask for project folder name
    project_folder_name = prompt_user_input(stdscr, "Nome cartella progetto:")
    if not project_folder_name or not project_folder_name.strip():
        return  # Cancel if no name provided
    
    # Clean the name (replace spaces with underscores)
    clean_project_name = project_folder_name.strip().replace(' ', '_')
    project_folder_path = os.path.join(folder_path, clean_project_name)
    
    try:
        # Create the project folder
        os.makedirs(project_folder_path, exist_ok=True)
        
        # Generate project name from the project folder name
        auto_name = generate_project_name_from_folder(clean_project_name)
        
        # Check if already exists and add counter if needed
        counter = 1
        original_name = auto_name
        while auto_name in config["project_map"]:
            auto_name = f"{original_name}_{counter}"
            counter += 1
        
        config["project_map"][auto_name] = project_folder_path
        config["last_opened_in_vscode"] = project_folder_path
        
        # Show creation success message
        stdscr.clear()
        if clean_project_name != project_folder_name.strip():
            stdscr.addstr(0, 2, f"✅ Cartella progetto '{clean_project_name}' creata!", curses.color_pair(2))
        else:
            stdscr.addstr(0, 2, f"✅ Cartella progetto '{clean_project_name}' creata!", curses.color_pair(2))
        stdscr.addstr(1, 2, f"📂 Percorso: {format_path_display(project_folder_path)}")
        
        # Always ask if they want to set it as active project
        stdscr.addstr(3, 2, f"Vuoi impostare '{auto_name}' come progetto attivo? (y/n)")
        key = stdscr.getch()
        should_activate = key == ord('y') or key == ord('Y')
        
        if should_activate:
            config["current_project"] = auto_name
        
        save_config(config)
        
        # Show final status and ask about VS Code
        stdscr.clear()
        if should_activate:
            stdscr.addstr(0, 2, f"✅ Progetto '{auto_name}' creato e attivato!", curses.color_pair(2))
        else:
            stdscr.addstr(0, 2, f"✅ Progetto '{auto_name}' creato!", curses.color_pair(2))
        
        stdscr.addstr(1, 2, f"📂 Cartella: {format_path_display(project_folder_path)}")
        stdscr.addstr(3, 2, "Vuoi aprire il progetto in VS Code? (y/n)")
        
        key = stdscr.getch()
        if key == ord('y') or key == ord('Y'):
            open_in_vscode(project_folder_path)
    
    except Exception as e:
        stdscr.clear()
        stdscr.addstr(0, 2, f"❌ Errore creazione cartella progetto: {str(e)}", curses.color_pair(1))
        stdscr.addstr(curses.LINES - 1, 2, "Premi un tasto per continuare...")
        stdscr.getch()
        return
    
    stdscr.addstr(curses.LINES - 1, 2, "Premi un tasto per continuare...")
    stdscr.getch()

def add_milestone(stdscr, config):
    """Navigate and create milestone folder, then optionally create project inside it"""
    current_path = BASE_REPO
    selection = 0

    while True:
        entries = list_entries(current_path)
        stdscr.clear()
        
        stdscr.addstr(0, 2, "🗂️ Aggiungi Milestone - Naviga e crea cartelle")
        stdscr.addstr(1, 2, f"📍 {format_path_display(current_path)}")
        stdscr.addstr(2, 2, "-" * (curses.COLS - 4))

        for idx, (name, is_dir) in enumerate(entries):
            icon = "📂" if is_dir else "📄"
            highlight = curses.A_REVERSE if idx == selection else curses.A_NORMAL
            stdscr.addstr(4 + idx, 2, f"{icon} {name}", highlight)

        # Key help at bottom
        help_y = curses.LINES - 2
        stdscr.addstr(help_y - 1, 2, "↑↓:Muovi | Invio:Entra | n:Crea cartella milestone")
        stdscr.addstr(help_y, 2, "Backspace:← | r:Root")

        key = stdscr.getch()
        if key == curses.KEY_UP and selection > 0:
            selection -= 1
        elif key == curses.KEY_DOWN and selection < len(entries) - 1:
            selection += 1
        elif key in [10, 13]:  # Invio - enter folder
            if not entries:
                continue
            name, is_dir = entries[selection]
            if is_dir:
                current_path = os.path.join(current_path, name)
                selection = 0
        elif key == ord("n"):  # Create new milestone folder
            folder_name = prompt_user_input(stdscr, "Nome nuova cartella milestone:")
            if folder_name and folder_name.strip():
                # Replace spaces with underscores for safety
                clean_name = folder_name.strip().replace(' ', '_')
                new_folder_path = os.path.join(current_path, clean_name)
                try:
                    os.makedirs(new_folder_path, exist_ok=True)
                    stdscr.clear()
                    if clean_name != folder_name.strip():
                        stdscr.addstr(0, 2, f"✅ Cartella milestone '{clean_name}' creata!", curses.color_pair(2))
                    else:
                        stdscr.addstr(0, 2, f"✅ Cartella milestone '{clean_name}' creata!", curses.color_pair(2))
                    
                    stdscr.addstr(1, 2, f"📂 Percorso: {format_path_display(new_folder_path)}")
                    stdscr.addstr(3, 2, "Vuoi creare un nuovo progetto in questa cartella? (y/n)")
                    
                    key = stdscr.getch()
                    if key == ord('y') or key == ord('Y'):
                        # Create project in the new milestone folder
                        create_project_in_folder(stdscr, config, new_folder_path)
                    else:
                        stdscr.addstr(5, 2, "Milestone creato senza progetto.")
                        stdscr.addstr(curses.LINES - 1, 2, "Premi un tasto per continuare...")
                        stdscr.getch()
                    
                    return  # Return to main menu after milestone creation
                    
                except Exception as e:
                    stdscr.clear()
                    stdscr.addstr(0, 2, f"❌ Errore creazione cartella: {str(e)}", curses.color_pair(1))
                    stdscr.addstr(curses.LINES - 1, 2, "Premi un tasto per continuare...")
                    stdscr.getch()
        elif key == curses.KEY_BACKSPACE or key == 127:
            if current_path != BASE_REPO:
                current_path = os.path.dirname(current_path)
                selection = 0
            else:
                return  # Return to main menu when at root
        elif key == ord("r"):
            current_path = BASE_REPO
            selection = 0

        stdscr.refresh()

def add_new_project(stdscr, config):
    """Add a new project - automatically generates name from folder"""
    # Select path with creation option
    selected_path = select_path_with_creation(stdscr, config)
    if selected_path:
        # Generate name from folder
        folder_name = os.path.basename(selected_path)
        auto_name = generate_project_name_from_folder(folder_name)
        
        # Check if already exists and add counter if needed
        counter = 1
        original_name = auto_name
        while auto_name in config["project_map"]:
            auto_name = f"{original_name}_{counter}"
            counter += 1
        
        # Check if project already exists (shouldn't happen with counter, but safety check)
        if auto_name in config["project_map"]:
            stdscr.clear()
            stdscr.addstr(0, 2, "❌ Errore: Progetto già esistente!", curses.color_pair(1))
            stdscr.addstr(curses.LINES - 1, 2, "Premi un tasto per continuare...")
            stdscr.getch()
            return
        
        config["project_map"][auto_name] = selected_path
        config["last_opened_in_vscode"] = selected_path
        
        # Ask if they want to set it as active project
        should_activate = True
        if config.get("current_project"):
            stdscr.clear()
            stdscr.addstr(0, 2, f"✅ Progetto '{auto_name}' creato!", curses.color_pair(2))
            stdscr.addstr(1, 2, f"📂 Cartella: {format_path_display(selected_path)}")
            stdscr.addstr(3, 2, f"Progetto attuale: {config['current_project']}")
            stdscr.addstr(4, 2, f"Vuoi impostare '{auto_name}' come progetto attivo? (y/n)")
            key = stdscr.getch()
            should_activate = key == ord('y') or key == ord('Y')
        
        if should_activate:
            config["current_project"] = auto_name
        
        save_config(config)
        
        # Ask if they want to open in VS Code
        if should_activate:
            stdscr.clear()
            stdscr.addstr(0, 2, f"✅ Progetto '{auto_name}' creato e attivato!", curses.color_pair(2))
            stdscr.addstr(1, 2, f"📂 Cartella: {format_path_display(selected_path)}")
            stdscr.addstr(3, 2, "Vuoi aprire il progetto in VS Code? (y/n)")
            key = stdscr.getch()
            if key == ord('y') or key == ord('Y'):
                open_in_vscode(selected_path)
        else:
            stdscr.clear()
            stdscr.addstr(0, 2, f"✅ Progetto '{auto_name}' creato!", curses.color_pair(2))
            stdscr.addstr(1, 2, f"📂 Cartella: {format_path_display(selected_path)}")
        
        stdscr.addstr(curses.LINES - 1, 2, "Premi un tasto per continuare...")
        stdscr.getch()

def edit_project(stdscr, config):
    """Edit an existing project"""
    projects = config.get("project_map", {})
    current_project = config.get("current_project")
    
    if not projects:
        stdscr.clear()
        stdscr.addstr(0, 2, "❌ Nessun progetto configurato!", curses.color_pair(3))
        stdscr.addstr(curses.LINES - 1, 2, "Premi un tasto per continuare...")
        stdscr.getch()
        return
    
    # Select project to edit with styled list
    selection = 0
    project_items = list(projects.keys())
    selected_project = None
    
    while True:
        stdscr.clear()
        stdscr.addstr(0, 2, "📝 Seleziona Progetto da Modificare")
        stdscr.addstr(1, 2, "-" * (curses.COLS - 4))
        
        y = 3
        for idx, name in enumerate(project_items):
            if y < curses.LINES - 3:
                highlight = curses.A_REVERSE if idx == selection else curses.A_NORMAL
                path = projects[name]
                
                if name == current_project:
                    stdscr.addstr(y, 2, f"🟢 {name} (ATTIVO)", highlight | curses.color_pair(2))
                    y += 1
                    stdscr.addstr(y, 4, f"📂 {format_path_short(path)}", highlight)
                else:
                    stdscr.addstr(y, 2, f"📋 {name}", highlight)
                    y += 1
                    stdscr.addstr(y, 4, f"📂 {format_path_short(path)}", highlight)
                y += 2
        
        stdscr.addstr(curses.LINES - 1, 2, "↑↓:Muovi | Invio:Seleziona | Backspace:Annulla")
        
        key = stdscr.getch()
        if key == curses.KEY_BACKSPACE or key == 127:
            return
        elif key == curses.KEY_UP and selection > 0:
            selection -= 1
        elif key == curses.KEY_DOWN and selection < len(project_items) - 1:
            selection += 1
        elif key in [10, 13]:  # ENTER
            selected_project = project_items[selection]
            break
    
    if not selected_project:
        return
    
    # Edit menu
    edit_selection = 0
    edit_menu = ["📝 Modifica nome", "📂 Modifica cartella"]
    
    while True:
        stdscr.clear()
        stdscr.addstr(0, 2, f"Modifica progetto: {selected_project}")
        stdscr.addstr(1, 2, f"Cartella: {format_path_display(projects[selected_project])}")
        stdscr.addstr(2, 2, "-" * (curses.COLS - 4))
        
        for idx, item in enumerate(edit_menu):
            y_pos = 4 + idx
            if y_pos < curses.LINES - 2:
                highlight = curses.A_REVERSE if idx == edit_selection else curses.A_NORMAL
                stdscr.addstr(y_pos, 3, item, highlight)
        
        stdscr.addstr(curses.LINES - 1, 2, "↑↓:Muovi | Invio:Seleziona | Backspace:Indietro")
        
        key = stdscr.getch()
        if key == curses.KEY_BACKSPACE or key == 127:
            break
        elif key == curses.KEY_UP and edit_selection > 0:
            edit_selection -= 1
        elif key == curses.KEY_DOWN and edit_selection < len(edit_menu) - 1:
            edit_selection += 1
        elif key in [10, 13]:  # ENTER
            if edit_selection == 0:  # Edit name
                new_name = prompt_user_input(stdscr, f"Nuovo nome per '{selected_project}':")
                if new_name and new_name.strip() and new_name != selected_project:
                    if new_name not in projects:
                        # Update project map
                        projects[new_name] = projects[selected_project]
                        del projects[selected_project]
                        # Update current project if needed
                        if config.get("current_project") == selected_project:
                            config["current_project"] = new_name
                        save_config(config)
                        
                        stdscr.clear()
                        stdscr.addstr(0, 2, "✅ Nome progetto aggiornato!", curses.color_pair(2))
                        stdscr.addstr(curses.LINES - 1, 2, "Premi un tasto per continuare...")
                        stdscr.getch()
                        break
                    else:
                        stdscr.clear()
                        stdscr.addstr(0, 2, "❌ Nome già esistente!", curses.color_pair(1))
                        stdscr.addstr(curses.LINES - 1, 2, "Premi un tasto per continuare...")
                        stdscr.getch()
            elif edit_selection == 1:  # Edit folder
                new_path = select_path_with_creation(stdscr, config)
                if new_path:
                    projects[selected_project] = new_path
                    save_config(config)
                    
                    stdscr.clear()
                    stdscr.addstr(0, 2, "✅ Cartella progetto aggiornata!", curses.color_pair(2))
                    stdscr.addstr(curses.LINES - 1, 2, "Premi un tasto per continuare...")
                    stdscr.getch()
                    break

def delete_project(stdscr, config):
    """Delete a project"""
    projects = config.get("project_map", {})
    current_project = config.get("current_project")
    
    if not projects:
        stdscr.clear()
        stdscr.addstr(0, 2, "❌ Nessun progetto configurato!", curses.color_pair(3))
        stdscr.addstr(curses.LINES - 1, 2, "Premi un tasto per continuare...")
        stdscr.getch()
        return
    
    # Select project to delete with styled list
    selection = 0
    project_items = list(projects.keys())
    selected_project = None
    
    while True:
        stdscr.clear()
        stdscr.addstr(0, 2, "🗑️ Seleziona Progetto da Eliminare")
        stdscr.addstr(1, 2, "-" * (curses.COLS - 4))
        
        y = 3
        for idx, name in enumerate(project_items):
            if y < curses.LINES - 3:
                highlight = curses.A_REVERSE if idx == selection else curses.A_NORMAL
                path = projects[name]
                
                if name == current_project:
                    stdscr.addstr(y, 2, f"🟢 {name} (ATTIVO)", highlight | curses.color_pair(2))
                    y += 1
                    stdscr.addstr(y, 4, f"📂 {format_path_short(path)}", highlight)
                else:
                    stdscr.addstr(y, 2, f"📋 {name}", highlight)
                    y += 1
                    stdscr.addstr(y, 4, f"📂 {format_path_short(path)}", highlight)
                y += 2
        
        stdscr.addstr(curses.LINES - 1, 2, "↑↓:Muovi | Invio:Seleziona | Backspace:Annulla")
        
        key = stdscr.getch()
        if key == curses.KEY_BACKSPACE or key == 127:
            return
        elif key == curses.KEY_UP and selection > 0:
            selection -= 1
        elif key == curses.KEY_DOWN and selection < len(project_items) - 1:
            selection += 1
        elif key in [10, 13]:  # ENTER
            selected_project = project_items[selection]
            break
    
    if not selected_project:
        return
    
    # Confirm deletion
    stdscr.clear()
    stdscr.addstr(0, 2, f"⚠️ Confermi eliminazione del progetto '{selected_project}'?", curses.color_pair(3))
    stdscr.addstr(2, 2, "y: Sì, elimina")
    stdscr.addstr(3, 2, "n: No, annulla")
    
    key = stdscr.getch()
    if key == ord('y') or key == ord('Y'):
        del projects[selected_project]
        # If it was the current project, set to None (no active project)
        if config.get("current_project") == selected_project:
            config["current_project"] = None
        save_config(config)
        
        stdscr.clear()
        stdscr.addstr(0, 2, f"✅ Progetto '{selected_project}' eliminato!", curses.color_pair(2))
        stdscr.addstr(curses.LINES - 1, 2, "Premi un tasto per continuare...")
        stdscr.getch()

def select_active_project(stdscr, config):
    """Select which project should be active"""
    projects = config.get("project_map", {})
    current_project = config.get("current_project")
    
    if not projects:
        stdscr.clear()
        stdscr.addstr(0, 2, "❌ Nessun progetto configurato!", curses.color_pair(3))
        stdscr.addstr(curses.LINES - 1, 2, "Premi un tasto per continuare...")
        stdscr.getch()
        return
    
    selection = 0
    project_items = list(projects.keys())
    
    while True:
        stdscr.clear()
        stdscr.addstr(0, 2, "🔄 Seleziona Progetto Attivo")
        stdscr.addstr(1, 2, "-" * (curses.COLS - 4))
        
        y = 3
        for idx, name in enumerate(project_items):
            if y < curses.LINES - 3:
                highlight = curses.A_REVERSE if idx == selection else curses.A_NORMAL
                path = projects[name]
                
                if name == current_project:
                    stdscr.addstr(y, 2, f"🟢 {name} (ATTIVO)", highlight | curses.color_pair(2))
                    y += 1
                    stdscr.addstr(y, 4, f"📂 {format_path_short(path)}", highlight)
                else:
                    stdscr.addstr(y, 2, f"📋 {name}", highlight)
                    y += 1
                    stdscr.addstr(y, 4, f"📂 {format_path_short(path)}", highlight)
                y += 2
        
        stdscr.addstr(curses.LINES - 1, 2, "↑↓:Muovi | Invio:Seleziona | Backspace:Annulla")
        
        key = stdscr.getch()
        if key == curses.KEY_BACKSPACE or key == 127:
            return
        elif key == curses.KEY_UP and selection > 0:
            selection -= 1
        elif key == curses.KEY_DOWN and selection < len(project_items) - 1:
            selection += 1
        elif key in [10, 13]:  # ENTER
            selected_project = project_items[selection]
            config["current_project"] = selected_project
            config["last_opened_in_vscode"] = projects[selected_project]
            save_config(config)
            
            stdscr.clear()
            stdscr.addstr(0, 2, f"✅ Progetto '{selected_project}' attivato!", curses.color_pair(2))
            stdscr.addstr(curses.LINES - 1, 2, "Premi un tasto per continuare...")
            stdscr.getch()
            return

def list_all_projects(stdscr, config):
    """Show all configured projects"""
    projects = config.get("project_map", {})
    current_project = config.get("current_project")
    
    stdscr.clear()
    stdscr.addstr(0, 2, "📋 Lista Progetti Configurati")
    stdscr.addstr(1, 2, "-" * (curses.COLS - 4))
    
    if not projects:
        stdscr.addstr(3, 2, "❌ Nessun progetto configurato", curses.color_pair(3))
    else:
        y = 3
        for name, path in projects.items():
            if y < curses.LINES - 2:
                if name == current_project:
                    stdscr.addstr(y, 2, f"🟢 {name} (ATTIVO)", curses.color_pair(2))
                    y += 1
                    stdscr.addstr(y, 4, f"📂 {format_path_short(path)}")
                else:
                    stdscr.addstr(y, 2, f"📋 {name}")
                    y += 1
                    stdscr.addstr(y, 4, f"📂 {format_path_short(path)}")
                y += 2
    
    stdscr.addstr(curses.LINES - 1, 2, "Premi un tasto per continuare...")
    stdscr.getch()

def select_from_list(stdscr, prompt, items):
    """Select an item from a list"""
    if not items:
        return None
    
    selection = 0
    while True:
        stdscr.clear()
        stdscr.addstr(0, 2, prompt)
        stdscr.addstr(1, 2, "-" * (curses.COLS - 4))
        
        for idx, item in enumerate(items):
            y_pos = 3 + idx
            if y_pos < curses.LINES - 2:
                highlight = curses.A_REVERSE if idx == selection else curses.A_NORMAL
                stdscr.addstr(y_pos, 3, item, highlight)
        
        stdscr.addstr(curses.LINES - 1, 2, "↑↓:Muovi | Invio:Seleziona | Backspace:Annulla")
        
        key = stdscr.getch()
        if key == curses.KEY_BACKSPACE or key == 127:
            return None
        elif key == curses.KEY_UP and selection > 0:
            selection -= 1
        elif key == curses.KEY_DOWN and selection < len(items) - 1:
            selection += 1
        elif key in [10, 13]:  # ENTER
            return items[selection]

def generate_project_name_from_folder(folder_name):
    """Generate a smart project name from folder name"""
    # Preserve original case for better pattern matching
    name = folder_name
    name_lower = folder_name.lower()
    
    # Handle 42 School patterns - preserve case where appropriate
    if name_lower.startswith('c_piscine'):
        return f"C_Piscine_{name.split('_')[-1].upper()}" if '_' in name else "C_Piscine"
    elif name_lower.startswith('cpp_'):
        return f"CPP_{name.split('_')[-1].capitalize()}"
    elif name_lower.startswith('ft_'):
        return name[3:].replace('_', ' ').title().replace(' ', '_')
    elif 'libft' in name_lower:
        return "Libft"
    elif 'printf' in name_lower:
        return "Printf" if 'printf' in name_lower else name
    elif 'get_next_line' in name_lower:
        return "Get_Next_Line"
    elif 'born2beroot' in name_lower:
        return "Born2beroot"
    elif 'minitalk' in name_lower:
        return "Minitalk"
    elif 'push_swap' in name_lower:
        return "Push_Swap"
    elif 'philosophers' in name_lower:
        return "Philosophers"
    elif 'minishell' in name_lower:
        return "Minishell"
    elif 'cub3d' in name_lower:
        return "Cub3D"
    elif 'webserv' in name_lower:
        return "Webserv"
    elif 'inception' in name_lower:
        return "Inception"
    elif 'transcendence' in name_lower:
        return "Transcendence"
    elif 'netpractice' in name_lower:
        return "NetPractice"  # Special case for NetPractice
    elif name_lower.startswith('ex') and name_lower[2:].isdigit():
        return f"Exercise_{name[2:]}"
    elif name.isdigit():
        return f"Day_{name}"
    else:
        # Generic cleanup: try to preserve original capitalization
        # Split by common separators and capitalize appropriately
        parts = []
        for part in name.replace('-', '_').split('_'):
            if part:
                # If part is all lowercase or all uppercase, capitalize it
                if part.islower() or part.isupper():
                    parts.append(part.capitalize())
                else:
                    # Keep mixed case as is
                    parts.append(part)
        return '_'.join(parts) if parts else name

def select_path_with_creation(stdscr, config):
    """Enhanced path selection with folder creation capability"""
    current_path = BASE_REPO
    selection = 0

    while True:
        entries = list_entries(current_path)
        stdscr.clear()
        
        stdscr.addstr(0, 2, "📂 Seleziona cartella progetto")
        
        stdscr.addstr(1, 2, f"📍 {format_path_display(current_path)}")
        stdscr.addstr(2, 2, "-" * (curses.COLS - 4))

        for idx, (name, is_dir) in enumerate(entries):
            icon = "📂" if is_dir else "📄"
            highlight = curses.A_REVERSE if idx == selection else curses.A_NORMAL
            stdscr.addstr(4 + idx, 2, f"{icon} {name}", highlight)

        # Key help at bottom with creation option
        help_y = curses.LINES - 2
        stdscr.addstr(help_y - 1, 2, "↑↓:Muovi | Invio:Entra | s:Seleziona questa cartella")
        stdscr.addstr(help_y, 2, "n:Crea nuova cartella | Backspace:← | r:Root")

        key = stdscr.getch()
        if key == curses.KEY_UP and selection > 0:
            selection -= 1
        elif key == curses.KEY_DOWN and selection < len(entries) - 1:
            selection += 1
        elif key in [10, 13]:  # Invio - enter folder
            if not entries:
                continue
            name, is_dir = entries[selection]
            if is_dir:
                current_path = os.path.join(current_path, name)
                selection = 0
        elif key == ord("s"):  # Select current folder
            return current_path
        elif key == ord("n"):  # Create new folder
            folder_name = prompt_user_input(stdscr, "Nome nuova cartella:")
            if folder_name and folder_name.strip():
                # Replace spaces with underscores for safety
                clean_name = folder_name.strip().replace(' ', '_')
                new_folder_path = os.path.join(current_path, clean_name)
                try:
                    os.makedirs(new_folder_path, exist_ok=True)
                    stdscr.clear()
                    if clean_name != folder_name.strip():
                        stdscr.addstr(0, 2, f"✅ Cartella '{clean_name}' creata!", curses.color_pair(2))
                        stdscr.addstr(0, 2, f"✅ Cartella '{clean_name}' creata!", curses.color_pair(2))
                    stdscr.addstr(2, 2, "Vuoi selezionare questa cartella? (y/n)")
                    key = stdscr.getch()
                    if key == ord('y') or key == ord('Y'):
                        return new_folder_path
                    # Refresh directory listing
                    selection = 0
                except Exception as e:
                    stdscr.clear()
                    stdscr.addstr(0, 2, f"❌ Errore creazione cartella: {str(e)}", curses.color_pair(1))
                    stdscr.addstr(curses.LINES - 1, 2, "Premi un tasto per continuare...")
                    stdscr.getch()
        elif key == curses.KEY_BACKSPACE or key == 127:
            if current_path != BASE_REPO:
                current_path = os.path.dirname(current_path)
                selection = 0
            else:
                return None  # Cancel
        elif key == ord("r"):
            current_path = BASE_REPO
            selection = 0

        stdscr.refresh()

def navigate_mode(stdscr, config):
    current_path = BASE_REPO
    selection = 0

    while True:
        entries = list_entries(current_path)

        stdscr.clear()
        stdscr.addstr(0, 2, f"📂 {format_path_display(current_path)}")
        stdscr.addstr(1, 2, "-" * (curses.COLS - 4))

        for idx, (name, is_dir) in enumerate(entries):
            icon = "📂" if is_dir else "📄"
            highlight = curses.A_REVERSE if idx == selection else curses.A_NORMAL
            stdscr.addstr(3 + idx, 2, f"{icon} {name}", highlight)

        # Key help at bottom
        if curses.LINES > 1:
            stdscr.addstr(curses.LINES - 1, 2, "Backspace:← | r:Root | Invio:Apri | o:VS Code | t:Terminale | e:Esplora")

        key = stdscr.getch()
        if key == curses.KEY_UP and selection > 0:
            selection -= 1
        elif key == curses.KEY_DOWN and selection < len(entries) - 1:
            selection += 1
        elif key in [10, 13]:  # Invio
            if not entries:
                continue
            name, is_dir = entries[selection]
            path = os.path.join(current_path, name)
            if is_dir:
                current_path = path
                selection = 0
            else:
                subprocess.Popen(["xdg-open", path])
        elif key == ord("o"):
            if not entries:
                continue
            name, _ = entries[selection]
            path = os.path.join(current_path, name)
            open_in_vscode(path)
            # Aggiorno l'ultimo file/cartella aperta solo se apro in VS Code
            config["last_opened_in_vscode"] = path
            save_config(config)
        elif key == ord("t"):
            # Apri terminale nella cartella corrente o nella cartella selezionata
            if entries:
                name, is_dir = entries[selection]
                if is_dir:
                    terminal_path = os.path.join(current_path, name)
                else:
                    terminal_path = current_path
            else:
                terminal_path = current_path
            open_in_terminal(terminal_path)
        elif key == ord("e"):
            # Apri esplora file nella cartella corrente o nella cartella selezionata
            if entries:
                name, is_dir = entries[selection]
                if is_dir:
                    explorer_path = os.path.join(current_path, name)
                else:
                    explorer_path = current_path
            else:
                explorer_path = current_path
            subprocess.Popen(["xdg-open", explorer_path])
        elif key == curses.KEY_BACKSPACE or key == 127:
            if current_path != BASE_REPO:
                current_path = os.path.dirname(current_path)
                selection = 0
            else:
                return  # Return to main menu when at root
        elif key == ord("r"):
            current_path = BASE_REPO
            selection = 0

        stdscr.refresh()

def main_menu(stdscr):
    curses.curs_set(0)
    curses.start_color()
    curses.use_default_colors()
    
    # Initialize color pairs for git status
    curses.init_pair(1, curses.COLOR_RED, -1)     # Red for errors
    curses.init_pair(2, curses.COLOR_GREEN, -1)   # Green for success  
    curses.init_pair(3, curses.COLOR_YELLOW, -1)  # Yellow for warnings

    menu_items = [
        "📂 Apri ultimo file/cartella",
        "📁 Apri progetto attuale",
        "📝 Gestisci progetti",
        "🧭 Naviga cartelle",
        "💻 Apri terminale",
        "⛔ Esci"
    ]
    selection = 0

    # ASCII art header - Superminal
    header = r"""
 ____                                  _             _ 
/ ___| _   _ _ __   ___ _ __ _ __ ___ (_)_ __   __ _| |
\___ \| | | | '_ \ / _ \ '__| '_ ` _ \| | '_ \ / _` | |
 ___) | |_| | |_) |  __/ |  | | | | | | | | | | (_| | |
|____/ \__,_| .__/ \___|_|  |_| |_| |_|_|_| |_|\__,_|_|
            |_|                                        
    """
    header_lines = [line for line in header.split('\n') if line.strip()]

    while True:
        # Refresh config and git status every time we return to main menu
        config = load_config()
        
        # Fetch git updates (in background) to get latest remote info
        try:
            subprocess.Popen(["git", "fetch"], cwd=BASE_REPO, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        except Exception:
            pass  # Ignore fetch errors silently
        
        stdscr.clear()
        
        # Display header if it fits (optimized for 80x24)
        if header_lines and curses.LINES >= 15:  # Need at least 15 lines for header + menu
            max_header_width = max(len(line) for line in header_lines)
            if max_header_width <= curses.COLS:
                start_y = 0
                for line in header_lines:
                    if start_y < curses.LINES - 10:  # Leave space for menu and help
                        try:
                            stdscr.addstr(start_y, 0, line)  # Use default colors
                        except curses.error:
                            pass  # Skip if can't fit
                        start_y += 1
                menu_start_row = start_y + 1
            else:
                menu_start_row = 0
        else:
            menu_start_row = 0

        # Display menu items
        for idx, item in enumerate(menu_items):
            y_pos = menu_start_row + idx
            if y_pos < curses.LINES - 2:
                highlight = curses.A_REVERSE if idx == selection else curses.A_NORMAL
                stdscr.addstr(y_pos, 3, item, highlight)

        # Current project indicator
        current_project = config.get("current_project")
        project_y = menu_start_row + len(menu_items) + 1
        if project_y < curses.LINES - 2:
            if current_project:
                stdscr.addstr(project_y, 3, f"📋 Progetto: {current_project}", curses.color_pair(2))
            else:
                stdscr.addstr(project_y, 3, "📋 Progetto: Nessuno configurato", curses.color_pair(3))

        # Git status indicator
        status_type, git_info = get_git_status()
        if status_type is not None:  # Only show if it's a git repo
            git_y = project_y + 1
            if git_y < curses.LINES - 2:
                if status_type == "clean":
                    stdscr.addstr(git_y, 3, "🟢 Git: All changes pushed", curses.color_pair(2))
                elif status_type == "modified":
                    stdscr.addstr(git_y, 3, "🔴 Git: Uncommitted changes (press 'g')", curses.color_pair(1))
                elif status_type == "unpushed":
                    stdscr.addstr(git_y, 3, "🟡 Git: Unpushed commits (press 'g')", curses.color_pair(3))
                elif status_type == "need_pull":
                    stdscr.addstr(git_y, 3, "🚨 Git: NEED TO PULL! Remote has changes (press 'g')", curses.color_pair(1))
                else:  # both
                    stdscr.addstr(git_y, 3, "🔴 Git: Changes & unpushed commits (press 'g')", curses.color_pair(1))

        # Key help at bottom
        if curses.LINES > 1:
            help_text = "↑↓:Muovi | Invio:Seleziona"
            if status_type is not None and status_type != "clean":
                help_text += " | g:Git Status"
            stdscr.addstr(curses.LINES - 1, 3, help_text)

        key = stdscr.getch()
        if key == curses.KEY_UP and selection > 0:
            selection -= 1
        elif key == curses.KEY_DOWN and selection < len(menu_items) - 1:
            selection += 1
        elif key == ord('g'):  # Git status
            status_type, git_info = get_git_status()
            if status_type != "clean" and status_type is not None:
                show_git_status_screen(stdscr, status_type, git_info)
        elif key in [10, 13]:  # ENTER
            if selection == 0:
                path = config.get("last_opened_in_vscode")
                if path and os.path.exists(path):
                    open_in_vscode(path)
            elif selection == 1:
                proj = config.get("current_project")
                if proj:
                    path = config["project_map"].get(proj)
                    if path and os.path.exists(path):
                        config["last_opened_in_vscode"] = path
                        save_config(config)
                        open_in_vscode(path)
            elif selection == 2:
                manage_projects_menu(stdscr, config)
            elif selection == 3:
                navigate_mode(stdscr, config)
            elif selection == 4:
                open_in_terminal(BASE_REPO)
            elif selection == 5:
                return
            
        stdscr.refresh()

if __name__ == "__main__":
    curses.wrapper(main_menu)