/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake_to_camel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:26:34 by igilani           #+#    #+#             */
/*   Updated: 2025/03/18 16:39:36 by igilani          ###   ########.fr       */
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
	{
		if (argv[1][i] == '_' && argv[1][i + 1] != '\0')
		{
			argv[1][i + 1] -= 32;
			i++;
		}
		if (argv[1][i] != '_')
			write(1, &argv[1][i], 1);
		i++;
	}
	write(1, "\n", 1);
	return(0);
}