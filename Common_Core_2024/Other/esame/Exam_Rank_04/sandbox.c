/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:24:12 by igilani           #+#    #+#             */
/*   Updated: 2025/08/19 19:14:22 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Allowed functions	:	fork, waitpid, exit, alarm, sigaction, kill, printf, strsignal, 
						errno, sigaddset, sigemptyset, sigfillset, sigdelset, sigismember
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t pid;
	int i = 0;
	int status;
	
	if (f == NULL)
		return(-1);

	pid = fork();

	if (pid == -1)
		return(-1);

	if (pid == 0)
	{
		alarm(timeout);
		f();
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 0)
				{}
		}
		if (WIFSIGNALED(status))
			return (WTERMSIG(status));
	}
}