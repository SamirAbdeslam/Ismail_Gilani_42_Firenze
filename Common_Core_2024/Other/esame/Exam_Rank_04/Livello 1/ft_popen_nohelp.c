/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen_nohelp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:15:53 by igilani           #+#    #+#             */
/*   Updated: 2025/08/26 16:34:26 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//pipe, fork, dup2, execvp, close, exit

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "./my_libft/libft.h"

int parsing(const char *file, char *const argv[], char type)
{
	if (type != 'r' && type != 'w')
		return (-1);
	else if (!file)
		return (-1);
	else if (!argv)
		return (-1);
	else
		return (1);
}

void child(const char *file, char *const argv[], char type, int *fd)
{
	if (type == 'r')
	{
		if (dup2(fd[1], 1) == -1)
		{
			close(fd[0]);
			close(fd[1]);
			exit(-1);
		}
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		if (dup2(fd[0], 0) == -1)
		{
			close(fd[1]);
			close(fd[0]);
			exit(-1);
		}
		close(fd[1]);
		close(fd[0]);
	}
	execvp(file, argv);
	exit(-1);
}

int	ft_popen(const char *file, char *const argv[], char type)
{
	int fd[2];
	pid_t pid;
	
	if (parsing(file, argv, type) == -1)
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
		child(file, argv, type, fd);
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

int	main()
{
	int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
	char	*line;
	while ((line = get_next_line(fd)))
		ft_putstr_fd(line, fd);
	return (0);
}
