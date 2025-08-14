/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:12:57 by igilani           #+#    #+#             */
/*   Updated: 2025/08/14 18:37:28 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_command {
	char **argv;
	int fd_input;
	int fd_output;
} t_command;

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return(*(unsigned char *)s1 - *(unsigned char *)s2);
	
}

int count_pipes(char **cmds)
{
	int i = 0;
	int j = 0;

	while (cmds[i])
	{
		if (ft_strcmp(cmds[i], "|") == 0)
		{
			printf("Trovato pipe a: %d\n", i);
			j++;
		}
		if (ft_strcmp(cmds[i], "|") != 0)
			printf("Trovato cmds a: %s - %d\n", cmds[i], i);
		i++;
	}
	return(j);
}

int	picoshell(char *cmds[])
{
	printf("pipes are: %d", count_pipes(cmds));
	return(0);
}

int main(int argc, char **argv)
{
	(void)argc;
	argv++;
	picoshell(argv);
	return(0);
}