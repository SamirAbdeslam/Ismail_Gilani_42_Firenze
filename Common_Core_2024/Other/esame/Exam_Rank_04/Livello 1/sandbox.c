/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:24:12 by igilani           #+#    #+#             */
/*   Updated: 2025/08/20 16:25:09 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Allowed functions	:	fork, waitpid, exit, alarm, sigaction, kill, printf, strsignal, 
						errno, sigaddset, sigemptyset, sigfillset, sigdelset, sigismember
*/

#include <stdio.h>     // Per printf
#include <stdlib.h>    // Per exit
#include <stdbool.h>   // Per bool
#include <unistd.h>    // Per fork, alarm
#include <sys/types.h> // Per pid_t
#include <sys/wait.h>  // Per waitpid
#include <signal.h>    // Per signal handling
#include <string.h>    // Non necessario ma utile per funzioni di stringa
#include <errno.h>     // Per errno

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t pid;
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
			{
				if (verbose)
					printf("Nice function!\n");
				return(1);	
			}
			else
			{
				if (verbose)
					printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
				return(0);
			}
		}
		if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (sig == SIGALRM)
			{
				if (verbose)
					printf("Bad function: timed out after %u seconds\n", timeout);
			}
			else
			{
				if (verbose)
					printf("Bad function: %s\n", strsignal(sig));
			}
			return(0);
		}
	}
	return (0);
}