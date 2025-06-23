/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:46:32 by igilani           #+#    #+#             */
/*   Updated: 2025/06/23 22:05:56 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

/*
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
Sono 11 argomenti
*/

int ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

void do_pipe(char **argv, char **env, int start)
{
	int fd[2];
	pid_t pid;
	
	pipe(fd);
	pid = fork();
	if (!pid)
	{
		dup2(fd[1], STDOUT_FILENO);
		execve(*argv,argv, env);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int main(int argc, char **argv, char **env)
{
	(void)env;
	(void)argc;
	int i = 1;
	int start = 1;

	while (argv[i])
	{
		if (!strcmp(argv[i], "|"))
		{
			argv[i] = NULL;
			do_pipe(argv, env, start);
			start = i + 1;
		}
		i++;
	}
	// ft_print(&argv[start]); QUI SI FA UN EXCEVE PER L'ULTIMO COMANDO DIO CRISTO
}