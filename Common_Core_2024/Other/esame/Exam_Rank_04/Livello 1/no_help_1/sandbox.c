/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:18:22 by igilani           #+#    #+#             */
/*   Updated: 2025/08/29 18:48:49 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	if (f == NULL)
		return (-1);
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		alarm(timeout);
		f();
		exit (0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 0)
			{
				if (verbose)
					printf("Nice function!\n");
				return (1);
			}
			else
			{
				if (verbose)
					printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
				return (0);
			}
		}
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGALRM)
			{
				if (verbose)
					printf("Bad function: timed out after %u seconds\n", timeout);
			}
			else
			{
				if (verbose)
					printf("Bad function: %s\n", strsignal(WTERMSIG(status)));
			}
			return (0);
		}
	}
	return (-1);
}
