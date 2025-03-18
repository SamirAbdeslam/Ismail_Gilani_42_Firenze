/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:46:01 by igilani           #+#    #+#             */
/*   Updated: 2025/03/18 17:22:08 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int check_word(char *str, char c, int i, int check)
{
	while (i >= 0)
	{
		if (str[i] == c)
			check += 1;
		if (check == 2)
			return(0);
		i--;
	}
	if (check == 0)
		return (0);
	return(1);
}

int main(int argc, char **argv)
{
	int i = 0;
	int j = 0;
	if (argc != 3)
	{
		write(1, "\n", 1);
		return(0);
	}
	while (argv[1][i])
	{
		if (check_word(argv[1], argv[1][i], i, 0))
			write(1, &argv[1][i], 1);
		i++;
	}
	write(1, " ", 1);
	while (argv[2][j])
	{
		if (check_word(argv[1], argv[2][j], i, 1) && check_word(argv[2], argv[2][j], j, 0))
			write(1, &argv[2][j], 1);
		j++;
	}
	write(1, "\n", 1);
	return(0);
}