/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox_nohelp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:35:05 by igilani           #+#    #+#             */
/*   Updated: 2025/08/27 17:26:04 by igilani          ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

bool parsing(void (*f)(void), unsigned int timeout)
{
	if (f == NULL)
		return (false);
	else if (timeout < 0)
		return (false);
	else
		return (true);
}

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	if (parsing(f, timeout) == false)
		return (-1);

	int status = 0;
	pid_t pid;
	
	pid = fork();

	if (pid < 0)
		exit(-1);
	if (pid == 0)
	{
		alarm(timeout); //prima allarme POI FUNZIONE
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
			}
			else
			{
				if (verbose)
					printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
			}
			return (WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGALRM)
			{
				if (verbose)
					printf("Bad function: timed out after %d seconds\n", timeout);
			}
			else
			{
				if (verbose)
					printf("Bad function: %s\n", strsignal(WTERMSIG(status))); //bisogna passare il TERMSIGN a strsignal
			}
			return (WTERMSIG(status));
		}
		else
		{
			
			return (WEXITSTATUS(status));
		}
	}
	return (-1);
}

/* Nice function */
void	nice_function(void)
{
	printf("\n1. Hello from nice_function!\n");
}

/* Causes segmentation fault */
void	segfault_function(void)
{
	printf("\n2. Segfault function\n");
	int	*ptr = NULL;
	*ptr = 42;
}

/* Runs forever */
void	infinite_loop(void)
{
	printf("\n3. Infinite loop function\n");
	while (1) {}
}

/* Exits with error code 42 */
void	exit_with_error(void)
{
	printf("\n4. Exit_with_error function\n");
	exit(42);
}

void segfault_function_2(void) 
{
	printf("\n5. Segfault function\n");
	*(volatile char *)0 = 0;
}

void abnormal_termination(void) 
{
	printf("\n6. Abnormal termination function\n");
	abort();
}

int	main()
{
	printf("----- SANDBOX VERBOSE -----\n");
	sandbox(nice_function, 5, true);
	sandbox(segfault_function, 5, true);
	sandbox(infinite_loop, 2, true);
	sandbox(exit_with_error, 5, true);
	sandbox(segfault_function_2, 5, true);
	sandbox(abnormal_termination, 5, true);
	printf("\n----- SANDBOX NON VERBOSE -----\n");
	printf("Return code: %d\n", sandbox(nice_function, 5, false));
	printf("Return code: %d\n", sandbox(segfault_function, 5, false));
	printf("Return code: %d\n", sandbox(infinite_loop, 2, false));
	printf("Return code: %d\n", sandbox(exit_with_error, 5, false));
	printf("Return code: %d\n", sandbox(segfault_function_2, 5, false));
	printf("Return code: %d\n", sandbox(abnormal_termination, 5, false));
	return (0);
}