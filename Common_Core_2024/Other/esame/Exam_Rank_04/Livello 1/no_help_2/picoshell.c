/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:32:00 by igilani           #+#    #+#             */
/*   Updated: 2025/08/28 14:17:37 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Allowed functions:	close, fork, wait, exit, execvp, dup2, pipe

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

int	picoshell(char **cmds[])
{
	int fd[2];
	int in_fd = -1;
	pid_t pid;
	int i = 0;

	while (cmds[i])
	{
		if (cmds[i + 1])
		{
			if (pipe(fd) < 0)
				return (1);
		}
		pid = fork();

		if (pid < 0)
		{
			if (in_fd != -1)
			{
				close(in_fd);
				close(fd[0]);
				close(fd[1]);
				return (1);
			}
		}
		if (pid == 0)
		{
			if (in_fd != -1)
			{
				dup2(in_fd, STDIN_FILENO);
				//gestione errori
				close(in_fd);
			}
			if (cmds[i + 1])
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit (1);
		}
		if (in_fd != -1)
			close(in_fd);
		if (cmds[i + 1])
		{
			close(fd[1]);
			in_fd = fd[0];
		}
		i++;
	}
	while(wait(NULL) > 0)
		;
	return(0);
}