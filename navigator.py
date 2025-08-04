from pathlib import Path
import subprocess
import json
import os

# Percorsi principali
CONFIG_PATH = Path.home() / ".navigator_config.json"
ROOT_DIR = Path.home() / "Ismail_Gilani_42_Firenze"

# Inizializza la configurazione
def load_config():
    if not CONFIG_PATH.exists():
        config = {
            "last_opened_file_or_folder": None,
            "current_project": {"name": None, "path": None}
        }
        save_config(config)
    else:
        with open(CONFIG_PATH) as f:
            config = json.load(f)
    return config

def save_config(config):
    with open(CONFIG_PATH, "w") as f:
        json.dump(config, f, indent=4)

# Comandi utility
def open_with_code(path):
    subprocess.run(["code", str(path)])

def open_terminal(path):
    subprocess.run(["gnome-terminal", "--working-directory", str(path)])

# Formattazione
def format_path(path):
    try:
        return str(path.relative_to(ROOT_DIR))
    except ValueError:
        return str(path)

# Interfaccia utente
def main_menu(config):
    from rich.console import Console
    from rich.table import Table
    from prompt_toolkit import prompt
    from prompt_toolkit.completion import WordCompleter

    console = Console()
    while True:
        os.system("clear")
        console.print("[bold cyan]🧭 Project Navigator[/bold cyan]\n")

        table = Table(show_header=False, box=None)
        table.add_row("1.", "🟢 Apri ultimo file/cartella")
        table.add_row("2.", "🟡 Apri cartella progetto attuale")
        table.add_row("3.", "🔵 Seleziona progetto attuale")
        table.add_row("4.", "🧩 Apri terminale qui")
        table.add_row("5.", "📁 Naviga tra le cartelle")
        table.add_row("6.", "❌ Esci")
        console.print(table)

        choice = prompt("\nSeleziona un'opzione [1-6]: ").strip()

        if choice == "1":
            path = config.get("last_opened_file_or_folder")
            if path and Path(path).exists():
                open_with_code(path)
            else:
                console.print("[red]❗ Nessun file/cartella salvata.[/red]")
        elif choice == "2":
            path = config["current_project"]["path"]
            if path and Path(path).exists():
                open_with_code(path)
            else:
                console.print("[red]❗ Nessun progetto attuale selezionato.[/red]")
        elif choice == "3":
            new_name = prompt("🔤 Nome del progetto: ").strip()
            console.print("[green]📂 Naviga fino alla cartella del progetto e premi INVIO per selezionarla.[/green]")
            selected = navigate(ROOT_DIR)
            if selected:
                config["current_project"] = {"name": new_name, "path": str(selected)}
                save_config(config)
                console.print(f"[green]✅ Progetto '{new_name}' salvato.[/green]")
        elif choice == "4":
            open_terminal(ROOT_DIR)
        elif choice == "5":
            selected = navigate(ROOT_DIR)
            if selected:
                config["last_opened_file_or_folder"] = str(selected)
                save_config(config)
                open_with_code(selected)
        elif choice == "6":
            break
        else:
            console.print("[yellow]Inserisci un numero valido (1-6).[/yellow]")
        input("\nPremi INVIO per continuare...")

# Navigazione cartelle
def navigate(start_path):
    from prompt_toolkit.shortcuts import checkboxlist_dialog
    current = Path(start_path)
    while True:
        items = [("🔙 Torna indietro", "..")]
        for item in sorted(current.iterdir()):
            if item.name == ".git":
                continue
            icon = "📂" if item.is_dir() else "📄"
            items.append((f"{icon} {item.name}", str(item)))

        from prompt_toolkit.shortcuts import radiolist_dialog
        result = radiolist_dialog(
            title=f"Naviga in: {format_path(current)}",
            text="Seleziona una cartella o file:",
            values=[(val, label) for label, val in items]
        ).run()

        if not result:
            return None
        elif result == "..":
            if current != ROOT_DIR:
                current = current.parent
        else:
            path = Path(result)
            if path.is_dir():
                current = path
            else:
                return path

# Esegui
config = load_config()
main_menu(config)
