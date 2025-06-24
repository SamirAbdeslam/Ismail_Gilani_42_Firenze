/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:46:32 by igilani           #+#    #+#             */
/*   Updated: 2025/06/24 17:54:49 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

/*
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
Sono 11 argomenti
*/

void handle_error()
{
	write(2, "error: fatal\n", 14);
	exit(EXIT_FAILURE);
}

int do_pipe(char **argv, char **env, int old_fd, int pipe_need)
{
	int fd[2];
	pid_t pid;

	if (pipe(fd) == -1)
		handle_error();
	else
	{
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
			handle_error();
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(old_fd);
			if (pipe_need)
			{
				close(fd[1]);
				return (fd[0]);
			}
			else
				close(fd[0]);
		}
	}
	return(old_fd);
}

int main(int argc, char **argv, char **env)
{
	(void)env;
	(void)argc;
	int i = 1;
	int start = 1;
	int old_fd;

	old_fd = dup(STDIN_FILENO);

	while (argv[i])
	{
		if (!strcmp(argv[i], "|") || !strcmp(argv[i], ";"))
		{
			int is_pipe = !strcmp(argv[i], "|");
			argv[i] = NULL;
			old_fd = do_pipe(&argv[start], env, old_fd, is_pipe);
			start = i + 1;
		}
		i++;
	}
	if (start < argc)
		do_pipe(&argv[start], env, old_fd, 0);
	if (old_fd != STDIN_FILENO)
		close(old_fd);
}
