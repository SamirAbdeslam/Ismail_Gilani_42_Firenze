/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:41:27 by igilani           #+#    #+#             */
/*   Updated: 2025/03/18 12:03:03 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int check_word(char *str, char c, int i)
{
	int check = 0;
	
	while (i >= 0)
	{
		if (str[i] == c)
			check += 1;
		if (check == 2)
			return(1);
		i--;
	}
	return(0);
}

int main(int argc, char **argv)
{
	int i = 0;
	int j;

	if (argc != 3)
	{
		write(1, "\n", 1);
		return(0);
	}
	
	while (argv[1][i])
	{
		j = 0;
		while (argv[2][j])
		{
			if (argv[1][i] == argv[2][j] && (!(check_word(argv[1], argv[1][i], i))))
			{
				write(1, &argv[1][i], 1);
				break;
			}
			j++;
		}
		i++;
	}
	write(1, "\n", 1);
	return(0);
}