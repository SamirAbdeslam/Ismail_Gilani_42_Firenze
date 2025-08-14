/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:12:57 by igilani           #+#    #+#             */
/*   Updated: 2025/08/14 21:15:43 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		{
			//controllo l'indice di inizio e fine del comando
			printf("cmds are: %s in: %d\n",cmds[i], i);
		}
		i++;
	}
	return(j);
}

// void save_cmd(char **cmds, int n_cmds)
// {
// 	int i = 0;
// 	int j = 0;
// 	char *args[n_cmds];

// 	while (cmds[i])
// 	{
// 		if (ft_strcmp(cmds[i], "|") != 0)
// 			args[j] = cmds[i];
// 		i++;
// 	}
// }

int	picoshell(char *cmds[])
{
	// int n_cmds = count_pipes + 1;
	printf("pipes are: %d", count_pipes(cmds));
	// save_cmd(cmds, n_cmds);
	return(0);
}

int main(int argc, char **argv)
{
	(void)argc;
	argv++;
	picoshell(argv);
	return(0);
}