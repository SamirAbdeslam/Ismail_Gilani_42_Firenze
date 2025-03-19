/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidenp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:19:25 by igilani           #+#    #+#             */
/*   Updated: 2025/03/19 13:56:27 by igilani          ###   ########.fr       */
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
		if (check == 3)
			return(0);
		i--;
	}
	if (check == 0)
		return(0);
	return(1);
}

int ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return(i);
}

int main(int argc, char **argv)
{
	int i = 0;
	int correct = 0;
	int j = 0;

	if (argc != 3)
	{
		write(1, "\n", 1);
		return(0);
	}
	int check = ft_strlen(argv[1]);
	
	while (argv[1][i])
	{
		while (argv[2][j])
		{
			if (argv[1][i] == argv[2][j] && check_word(argv[2], argv[2][j], j))
			{
				correct++;
				break;
			}
			j++;
		}
		i++;
	}
	if (correct == check)
		write(1, "1", 1);
	else
		write(1, "0", 1);
	return(0);
}