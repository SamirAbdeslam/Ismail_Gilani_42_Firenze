/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell_nuovo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:13:26 by igilani           #+#    #+#             */
/*   Updated: 2025/06/25 23:11:57 by igilani          ###   ########.fr       */
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

	while(str[i])
		i++;
	return(i);
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
		write(2, "error: cannot executec ", 23);
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
	if (pipe_need && pipe(fd) == -1)
		handle_error(1, NULL);
	pid = fork();
	if (!pid)
	{
		dup2(old_fd, STDIN_FILENO);
		close(old_fd);
		if (pipe_need)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			close(fd[0]);
		}
		execve(*argv, argv, env);
		handle_error(3, *argv);
	}
	else
	{
		close(old_fd);
		if (pipe_need)
		{
			close(fd[1]);
			return (fd[0]);
		}
		else
		{
			waitpid(pid, NULL, 0);
			return (dup(STDIN_FILENO));
		}
	}
	return (old_fd);  // Non dovrebbe mai arrivare qui
}

int main(int argc, char **argv, char **env)
{
	int i = 1;
	int start = 1; 
	int old_fd;
	int is_pipe;
	old_fd = dup(STDIN_FILENO);

	while (argv[i] && i < argc)
	{
		if (!strcmp(argv[i], "|") || !strcmp(argv[i], ";"))
		{
			is_pipe = !strcmp(argv[i], "|");
			argv[i] = NULL;
			if (start < i && argv[start] != NULL)  // Controlla che ci sia un comando valido
			{
				old_fd = do_pipe(&argv[start], env, old_fd, is_pipe);
			}
			start = i + 1;
		}
		i++;
	}
	if (start < argc && argv[start] != NULL)  // Controlla che ci sia un comando valido
		do_pipe(&argv[start], env, old_fd, 0);
	else if (old_fd != STDIN_FILENO)  // Se c'è una pipe finale senza comando
	{
		close(old_fd);
		// Aspetta tutti i processi rimanenti
		while (waitpid(-1, NULL, 0) > 0);
	}
	else
		close(old_fd);
	return (0);
}