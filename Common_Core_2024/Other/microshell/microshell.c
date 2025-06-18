/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:46:32 by igilani           #+#    #+#             */
/*   Updated: 2025/06/18 21:56:07 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int tmp;
/*
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
Sono 11 argomenti
*/

void do_pipe(char **cmd, char **env, int i)
{
	pid_t pid;
	int fd[2];

	if (pipe(fd) == -1)
		write(2, "error: fatal\n", 13);
	pid = fork();
	if (!pid)
	{
		cmd[i] = 0;
		dup2(tmp, STDOUT_FILENO);
		close(tmp);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(*cmd, cmd, env);
		return ((void)write(2, "error: cannot execute ", 22));
	}
	else
	{
		dup2(0, tmp);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, NULL, 0);
	}
}

int main(int argc, char **argv, char **env)
{
	int tmp;
	int i;
	(void)argc;

	tmp = dup(0);
	if (tmp == -1)
		return (write(2, "error: fatal\n", 13));
	while (argv[i] && argv[++i])
	{
		argv = argv + i;
		i = 0;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;
		if (!strcmp(argv[i], "cd"))
			printf("Sono %d argomenti\n", i);
		else if (i)
			do_pipe(argv, env, i);
	}
	dup2(0, tmp);
	close(tmp);
}