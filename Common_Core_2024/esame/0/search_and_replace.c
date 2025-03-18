/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:57:41 by igilani           #+#    #+#             */
/*   Updated: 2025/03/17 16:15:01 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int i = 0;
	if (argc != 4)
	{
		write(1, "\n", 1);
		return(0);
	}
	if ((argv[2][0] == '\0' || argv[2][1] != '\0') || (argv[3][0] == '\0' || argv[3][1] != '\0'))
	{
		write(1, "\n", 1);
		return(0);
	}
	while (argv[1][i])
	{
		if(argv[1][i] == argv[2][0])
			argv[1][i] = argv[3][0];
		write(1, &argv[1][i], 1);
		i++;
	}
	write(1, "\n", 1);
	return(0);
}