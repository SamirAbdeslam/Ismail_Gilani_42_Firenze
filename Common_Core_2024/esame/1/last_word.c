/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:24:32 by igilani           #+#    #+#             */
/*   Updated: 2025/03/18 15:52:47 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int i = 0;
	if (argc != 2)
	{
		write(1, "\n", 1);
		return(0);
	}
	while (argv[1][i])
		i++;
	i--;
	while (argv[1][i] == ' ' || argv[1][i] == '\t')
		i--;
	while (argv[1][i] != ' ' && argv[1][i] != '\t')
		i--;
	i++;
	while (argv[1][i] && argv[1][i] != ' ' && argv[1][i] != '\t')
	{
		write(1, &argv[1][i], 1);
		i++;
	}
	write(1, "\n", 1);
	return(0);
}