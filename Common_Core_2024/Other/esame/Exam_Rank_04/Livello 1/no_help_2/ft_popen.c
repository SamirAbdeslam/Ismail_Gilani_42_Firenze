/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:04:33 by igilani           #+#    #+#             */
/*   Updated: 2025/08/27 18:31:29 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Allowed functions:	: pipe, fork, dup2, execvp, close, exit

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include "../my_libft/libft.h"
#include <sys/wait.h>

bool parsing(const char *file, char *const argv[], char type)
{
	if (type != 'w' && type != 'r')
		return (false);
	if (argv[0] == NULL)
		return (false);
	if (file == NULL)
		return (false);
	return (true);
}

int	ft_popen(const char *file, char *const argv[], char type)
{
	if (!parsing(file, argv, type))
		return (-1);
	int fd[2];
	pid_t pid;

	if (pipe(fd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			if (dup2(fd[1], STDOUT_FILENO) < 0)
			{
				close(fd[0]);
				close(fd[1]);
				return (-1);
			}
			close(fd[0]);
			close(fd[1]);
		}
		else
		{
			if (dup2(fd[0], STDIN_FILENO) < 0)
			{
				close(fd[0]);
				close(fd[1]);
				return (-1);
			}
			close(fd[1]);
			close(fd[0]);
		}
		execvp(file, argv);
		exit (-1);
	}
	else
	{
		if (type == 'r')
		{
			close(fd[1]);
			return (fd[0]); //ricordarsi di invertire
		}
		else
		{
			close(fd[0]);
			return (fd[1]); //ricordarsi di invertire
		}
	}
	return (-1);
}
