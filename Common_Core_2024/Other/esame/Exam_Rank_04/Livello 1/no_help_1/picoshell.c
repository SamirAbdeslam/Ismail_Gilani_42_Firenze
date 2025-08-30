/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:05:46 by igilani           #+#    #+#             */
/*   Updated: 2025/08/30 17:41:01 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int	picoshell(char **cmds[])
{
	int i = 0;
	int fd[2];
	int in_fd = -1;
	pid_t pid;

	while(cmds[i])
	{
		if (cmds[i + 1])
		{
			if (pipe(fd) < 0)
			{
				if (in_fd != -1)
					close(in_fd);
				return (1);
			}
		}
		pid = fork();
		if (pid < 0)
		{
			if (in_fd != -1)
				close(in_fd);
			return (1);
		}
		if (pid == 0)
		{
			if (in_fd != -1)
			{
				if (dup2(in_fd, 0) < 0)
				{
					close(fd[0]);
					close(fd[1]);
					close(in_fd);
					exit (1);
				}
				close(in_fd);
			}
			if (cmds[i + 1])
			{
				if (dup2(fd[1], 1) < 0)
				{
					if (in_fd != -1)
						close(in_fd);
					close(fd[0]);
					close(fd[1]);
					exit (1);
				}
				close(fd[0]);
				close(fd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit (1);
		}
		else
		{
			if (in_fd != -1)
				close(in_fd);
			if (cmds[i + 1])
			{
				close(fd[1]);
				in_fd = fd[0];
			}
		}
		i++;
	}
	while (wait(NULL) > 0)
		;
	return (0);
}