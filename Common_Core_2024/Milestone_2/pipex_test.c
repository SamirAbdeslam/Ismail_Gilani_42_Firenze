/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 21:26:34 by igilani           #+#    #+#             */
/*   Updated: 2025/01/29 21:57:04 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
    int	fd[2];
    
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return (1); // Exit status 1: Usage error
    }

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return (2); // Exit status 2: Pipe creation error
    }

    pid_t	pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (3); // Exit status 3: Fork error
    }

    if (pid == 0)
    {
        // Processo figlio
        close(fd[1]); // Chiude il lato di scrittura del pipe
        int x;
        if (read(fd[0], &x, sizeof(x)) == -1)
        {
            perror("read");
            return (4); // Exit status 4: Read error
        }
        printf("Ricevuto %d\n", x);
        close(fd[0]);
    }
    else
    {
        // Processo padre
        close(fd[0]); // Chiude il lato di lettura del pipe
        int y = atoi(argv[1]);
        if (write(fd[1], &y, sizeof(y)) == -1)
        {
            perror("write");
            return (5); // Exit status 5: Write error
        }
        printf("Scritto %d\n", y);
        close(fd[1]);
        wait(NULL);
    }
    return (0); // Exit status 0: Success
}
