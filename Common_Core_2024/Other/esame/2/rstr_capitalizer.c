/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rstr_capitalizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:42:43 by igilani           #+#    #+#             */
/*   Updated: 2025/03/19 16:43:08 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int i = 0;
	if (argc == 1)
	{
		write(1, "\n", 1);
		return(0);
	}
	int j = 1;
	while (j < argc)
	{
		i = 0;
		while (argv[j][i] && (argv[j][i] == ' ' || argv[j][i] == '\t'))
		{
			write(1, &argv[j][i], 1);
			i++;
		}
		while (argv[j][i] && (argv[j][i] != ' ' || argv[j][i] != '\t'))
		{
			if (argv[j][i] >= 'A' && argv[j][i] <= 'Z' && argv[j][i])
				argv[j][i] += 32;
			if ((argv[j][i] >= 'a' && argv[j][i] <= 'z') && (argv[j][i + 1] == ' ' || argv[j][i + 1] == '\t' || argv[j][i + 1] == '\0'))
				argv[j][i] -= 32;
			write(1, &argv[j][i], 1);
			i++;
		}
		write(1, "\n", 1);
		j++;
	}
	return(0);
}