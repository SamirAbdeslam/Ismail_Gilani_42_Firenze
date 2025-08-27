/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell_nohelp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:35:41 by igilani           #+#    #+#             */
/*   Updated: 2025/08/27 14:34:23 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//close, fork, wait, exit, execvp, dup2, pipe

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int	picoshell(char **cmds[])
{
	int fd[2];
	pid_t pid;
	int in_fd = -1;
	int i = 0;

	while(cmds[i])
	{
		if (cmds[i + 1] != NULL)
		{
			if (pipe(fd) < 0)
				return (1);
		}
		pid = fork();

		if (pid < 0)
		{
			if (cmds[i + 1] != NULL)
			{
				close(fd[0]);
				close(fd[1]);
			}
			return (1);
		}
		if (pid == 0)
		{
			if (in_fd != -1)
			{
				if (dup2(in_fd, STDIN_FILENO) < 0)
				{
					close(fd[0]);
					close(fd[1]);
					
					exit(1);
				}
				close(in_fd); //ciudere sempre o leak fd
			}
			if (cmds[i + 1] != NULL)
			{
				if (dup2(fd[1], STDOUT_FILENO) < 0)
				{
					close(fd[0]);
					close(fd[1]);
					close(in_fd);
					exit(1);
				}
				close(fd[0]); //ciudere sempre o leak fd
				close(fd[1]); //ciudere sempre o leak fd
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		else
		{
			if (in_fd != -1)
				close(in_fd);
			if (cmds[i + 1] != NULL)
			{
				in_fd = fd[0]; //non chiudere fd[0]
				close(fd[1]);
			}
		}
		i++;
	}
	while(wait(NULL) > 0)
		;
	return(0);
}



// int	picoshell(char **cmds[])
// {
// 	pid_t pid;
// 	int fd[2];
// 	int in_fd = -1;
// 	int i = 0;
	
// 	while(cmds[i])
// 	{
// 		if (cmds[i + 1] != NULL)
// 		{
// 			pipe(fd);
// 		}
// 		pid = fork();
// 		if (pid < 0)
// 		{
// 			close(fd[0]);
// 			close(fd[0]);
// 			return (1);
// 		}
// 		if (pid == 0)
// 		{
// 			if (in_fd != -1)
// 			{
// 				dup2(in_fd, STDIN_FILENO);
// 				close(in_fd);
// 			}
// 			if (cmds[i + 1] != NULL)
// 			{
// 				dup2(fd[1], STDOUT_FILENO);
// 				close(fd[0]);
// 				close(fd[1]);
// 			}
// 			execvp(cmds[i][0], cmds[i]);
// 			exit(-1);
// 		}
// 		else
// 		{
// 			if (in_fd != -1)
// 				close(in_fd);
// 			if (cmds[i + 1] != NULL)
// 			{
// 				close(fd[1]);
// 				in_fd = fd[0];
// 			}
// 		}
// 		i++;
// 	}
// 	while(wait(NULL) > 0)
// 		;
// 	return (0);
// }
