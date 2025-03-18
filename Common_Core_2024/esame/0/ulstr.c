/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulstr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:13:59 by igilani           #+#    #+#             */
/*   Updated: 2025/03/17 17:18:27 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int i = 0;
	if (argc != 2)
	{
		write(1, "\n", 1);
		return(0);
	}
	while(argv[1][i])
	{
		if(argv[1][i] >= 'A' && argv[1][i] <= 'Z')
			argv[1][i] += 32;
		else if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
			argv[1][i] -= 32;
		write(1, &argv[1][i], 1);
		i++;
	}
	write(1, "\n", 1);
	return(0);
}