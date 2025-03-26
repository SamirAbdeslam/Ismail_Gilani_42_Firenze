/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_capitalizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:40:04 by igilani           #+#    #+#             */
/*   Updated: 2025/03/19 16:50:16 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int i = 0;
	int j = 1;
	if (argc == 1)
	{
		write(1, "\n", 1);
		return(0);
	}
	while (j < argc)
	{
		i = 0;
		while(argv[j][i])
		{
			if (argv[j][i] >= 'A' && argv[j][i] <= 'Z')
				argv[j][i] += 32;
			if (i == 0 && argv[j][i] >= 'a' && argv[j][i] <= 'z')
				argv[j][i] -= 32;
			if ((argv[j][i - 1] == ' ' || argv[j][i - 1] == '\t') && (argv[j][i] >= 'a' && argv[j][i] <= 'z'))
				argv[j][i] -= 32;
			write(1, &argv[j][i], 1);
			i++;	
		}
		write(1, "\n", 1);
		j++;
	}
	return(0);
}