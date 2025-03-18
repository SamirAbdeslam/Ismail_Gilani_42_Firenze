/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:29:22 by igilani           #+#    #+#             */
/*   Updated: 2025/03/17 15:56:46 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int i = 0;
	if(argc != 2)
	{
		write(1, "\n", 1);
		return(0);
	}
	// while (argv[1][i] != '\0')
	// {
	// 	if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
	// 		argv[1][i] = 'a' + ((argv[1][i] - 'a' + 1) % 26);
	// 	else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
	// 		argv[1][i] = argv[1][i] + 1;
	// 	write(1, &argv[1][i], 1);
	// 	i++;
	// }
	while (argv[1][i] != '\0')
	{
		if (argv[1][i] >= 'a' && argv[1][i] < 'z')
			argv[1][i] = argv[1][i] + 1;
		else if (argv[1][i] == 'z')
			argv[1][i] = 'a';
		else if (argv[1][i] >= 'A' && argv[1][i] < 'Z')
			argv[1][i] = argv[1][i] + 1;
		else if (argv[1][i] == 'Z')
			argv[1][i] = 'A';
		write(1, &argv[1][i], 1);
		i++;
	}
	return(0);
}