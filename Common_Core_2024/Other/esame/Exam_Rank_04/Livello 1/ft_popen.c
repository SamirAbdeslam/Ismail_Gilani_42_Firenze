/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:26:43 by igilani           #+#    #+#             */
/*   Updated: 2025/08/13 19:09:42 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

bool ft_validate(const char *file, char *const argv[], char type)
{
	if (type != 'w' && type != 'r')
	{
		printf("Errore type %c", type);
		return (false);
	}
	else if (file == NULL)
	{
		printf("Errore file");
		return (false);
	}
	else if (argv[0] == NULL)
	{
		printf("Errore argv");
		return (false);
	}
	return (true);
}

void child(const char *file, char *const argv[], char type, int *fd)
{
	if (type == 'r')
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
		{
			close(fd[0]);
			close(fd[1]);
			exit(-1);
		}
		close(fd[0]);
		close(fd[1]);
		execvp(file, argv);
		exit (-1);
	}
	else
	{
		if (dup2(fd[0], STDIN_FILENO) < 0)
		{
			close(fd[0]);
			close(fd[1]);
			exit(-1);
		}
		close(fd[0]);
		close(fd[1]);
		execvp(file, argv);
		exit (-1);
	}
}

int	ft_popen(const char *file, char *const argv[], char type)
{
	int fd[2];
	pid_t pid;

	if (!ft_validate(file, argv, type))
		return (-1);

	if (pipe(fd) == -1)
		return (-1);
	
	pid = fork();

	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	else if (pid == 0)
		child(file, argv, type, fd);
	if (type == 'r')
	{
		close(fd[1]);
		return(fd[0]);
	}
	else
	{
		close(fd[0]);
		return (fd[1]);
	}
}
