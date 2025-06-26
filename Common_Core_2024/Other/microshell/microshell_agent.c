/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell_agent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:46:32 by igilani           #+#    #+#             */
/*   Updated: 2025/06/26 12:47:16 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>

int ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

void handle_error(int status, char *str)
{
	if (status == 1)
	{
		write(2, "error: fatal\n", 14);
		exit(EXIT_FAILURE);
	}
	else if (status == 2)
	{
		write(2, "error: cd: cannot change directory to ", 39);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	else if (status == 3)
	{
		write(2, "error: cannot execute ", 22);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
	else if (status == 4)
		write(2, "error: cd: bad arguments\n", 26);
}

void do_cd(char **argv)
{
	int i = 1;
	if (argv[1] == NULL)
	{
		handle_error(4, NULL);
		return ;
	}
	while (argv[i])
		i++;
	if (i > 2)
		handle_error(4, NULL);
	else if (chdir(argv[i - 1]) == -1)
		handle_error(2, argv[i - 1]);
}

int do_pipe(char **argv, char **env, int old_fd, int pipe_need)
{
	int fd[2];
	pid_t pid;

	if (!strcmp(argv[0], "cd"))
	{
		do_cd(argv);
		return(old_fd);
	}
	
	// Crea pipe SOLO quando necessaria
	if (pipe_need && pipe(fd) == -1)
		handle_error(1, NULL);
		
	pid = fork();
	if (pid < 0)
		handle_error(1, NULL);
	else if (pid == 0)  // child
	{
		// Setup input da pipe precedente
		if (old_fd != STDIN_FILENO)
		{
			dup2(old_fd, STDIN_FILENO);
			close(old_fd);
		}
		
		// Setup output per pipe corrente
		if (pipe_need)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			close(fd[0]);
		}
		
		execve(argv[0], argv, env);
		handle_error(3, argv[0]);
	}
	else  // parent
	{
		// Aspetta SEMPRE ogni processo subito (come examshell)
		waitpid(pid, NULL, 0);
		
		// Chiudi old_fd se non è stdin
		if (old_fd != STDIN_FILENO)
			close(old_fd);
			
		// Gestisci pipe corrente
		if (pipe_need)
		{
			close(fd[1]);  // Chiudi write end
			return (fd[0]); // Ritorna read end per prossimo comando
		}
		
		return (dup(STDIN_FILENO));  // Reset per prossimo comando
	}
	return (old_fd);
}

int main(int argc, char **argv, char **env)
{
	int i = 1;
	int start = 1;
	int old_fd;

	old_fd = dup(STDIN_FILENO);
	while (argv[i] && i < argc)
	{
		if (strcmp(argv[i], "|") == 0 || strcmp(argv[i], ";") == 0)
		{
			int is_pipe = !strcmp(argv[i], "|");
			argv[i] = NULL;
			
			// Salta comandi vuoti (;; consecutivi)
			if (start < i && argv[start] != NULL)
			{
				old_fd = do_pipe(&argv[start], env, old_fd, is_pipe);
			}
				
			start = i + 1;
		}
		i++;
	}
	
	// Esegui ultimo comando se presente
	if (start < argc && argv[start] != NULL)
		do_pipe(&argv[start], env, old_fd, 0);
		
	// Cleanup finale
	if (old_fd != STDIN_FILENO)
		close(old_fd);
		
	return (0);
}
