/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell_nuovo2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:58:07 by igilani           #+#    #+#             */
/*   Updated: 2025/06/26 17:20:09 by igilani          ###   ########.fr       */
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

	if (!str)
		return(0);
	while (str[i])
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
		write(2, "error: cannot execute", 22);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	else if (status == 3)
	{
		write(2,)
	}
}

void do_cd(char **argv)
{
	int i = 1;
	
	while(argv[i])
		i++;
	if (i == 1 || i > 2)
		handle_error(3, NULL);
	else
	{
		if (chdir(argv[i - 1]) == -1)
			handle_error(4, argv[i - 1]);
	}	
}

int do_pipe(char **argv, char **env, int is_pipe, int old_fd)
{
	int fd[2];
	pid_t pid;

	if (is_pipe && pipe(fd) == -1)
		handle_error(1, NULL);
	pid = fork();
	if (pid < 0)
		handle_error(1, NULL);
	if (pid == 0)
	{
		if (is_pipe)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			close(fd[0]);
		}
		close(old_fd);
		execve(*argv, argv, env);
		handle_error(2, *argv);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(old_fd);
		if (is_pipe)
		{
			dup2(fd[0], STDIN_FILENO);
			old_fd = fd[0];
			close(fd[1]);
			close(fd[0]);
		}
		else
		{
			waitpid(pid, NULL, 0);
			old_fd = dup(STDIN_FILENO);
		}
	}
	return(old_fd);
}

int main(int argc, char **argv, char **env)
{
	int i = 1;
	int start = 1;
	int is_pipe = 0;
	int old_fd;

	old_fd = dup(STDIN_FILENO);
	while (i < argc)
	{
		if (!strcmp(argv[i], "|") || !strcmp(argv[i], ";"))
		{
			is_pipe = !strcmp(argv[i], "|");
			argv[i] = NULL;
			do_pipe(&argv[start], env, is_pipe, old_fd);
			start = i + 1;
		}
		else if (!strcmp(argv[i], "cd"))
		{
			argv[i] = NULL;
			do_cd(&argv[start]);
			start = i + 1;
		}
		i++;
	}
	if (start < argc)
		do_pipe(&argv[start], env, 0, old_fd);
	close(old_fd);
}