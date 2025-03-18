/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:13:52 by igilani           #+#    #+#             */
/*   Updated: 2025/03/17 14:32:27 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int i = 0;
	int j = 0;
	if (argc != 2)
	{
		write(1, "\n", 1);
		return(0);
	}
	while (argv[1][i])
	{
		j = 0;
		if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
		{
			while (j < argv[1][i] - 'A' + 1)
			{
				write(1, &argv[1][i], 1);
				j++;
			}
		}
		else if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
		{
			while (j < argv[1][i] - 'a' + 1)
			{
				write(1, &argv[1][i], 1);
				j++;
			}
		}
		else
			write(1, &argv[1][i], 1);
		i++;
	}
	return(0);
}