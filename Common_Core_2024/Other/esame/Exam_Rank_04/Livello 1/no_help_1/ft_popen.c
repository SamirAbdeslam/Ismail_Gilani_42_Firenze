/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:41:18 by igilani           #+#    #+#             */
/*   Updated: 2025/08/29 12:57:29 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

bool parsing(const char *file, char *const argv[], char type)
{
	if (file == NULL)
		return (false);
	else if (argv[0] == NULL)
		return (false);
	else if (type != 'r' && type != 'w')
		return (false);
	else
		return (true);
}

int	ft_popen(const char *file, char *const argv[], char type)
{
	if (parsing(file, argv, type) == false)
		return (-1);
	int fd[2];
	pid_t pid;
	if (pipe(fd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (type == 'r')
		{
			if (dup2(fd[1], 1) < 0)
			{
				close(fd[0]);
				close(fd[1]);
				exit (-1);
			}
			close(fd[0]);
			close(fd[1]);
		}
		else
		{
			if (dup2(fd[0], 0) < 0)
			{
				close(fd[0]);
				close(fd[1]);
				exit (-1);
			}
			close(fd[0]);
			close(fd[1]);
		}
		execvp(file, argv);
		exit (-1);
	}
	else
	{
		if (type == 'r')
		{
			close(fd[1]);
			return(fd[0]);
		}
		else
		{
			close(fd[0]);
			return(fd[1]);
		}
	}
}
