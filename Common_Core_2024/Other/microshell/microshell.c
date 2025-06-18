/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:46:32 by igilani           #+#    #+#             */
/*   Updated: 2025/06/18 20:32:20 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void do_pipe(char *cmd_path, char **cmd, char **env, int cmd_index)
{
	int fd[2];
	pid_t pid;
	(void)cmd_index;

	if (pipe(fd) == -1)
		write(2, "error: fatal", 12);
	pid = fork();
	if (pid == -1)
		write(2, "error: fatal", 12);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (execve(cmd_path, cmd, env) == -1)
		{
			close(0);
			close(1);
			write(2, "error: cannot execute ", 23);
			write(2, cmd_path, strlen(cmd_path));
			write(2, "\n", 1);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

/*
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
Sono 11 argomenti
*/

int main(int argc, char **argv, char **env)
{
	int i = 1;
	char *cmd;

	cmd = NULL;
	while (i < argc - 1)
	{
		if (strcmp(argv[i], "|"))
		{
			printf("%s - %d\n", argv[i], i);
			if (cmd)
				free(cmd);
			cmd = strdup(argv[i]);
			printf("Command: %s\n", cmd);
			do_pipe(cmd, &cmd, env, i);
		}
		// else if (!strcmp(argv[i], ";"))
		// 	printf("%s - %d\n", argv[i], i);
		i++;
	}
}