/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprime.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:06:28 by igilani           #+#    #+#             */
/*   Updated: 2025/03/13 12:31:43 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	calculate(int nbr)
{
	int i = 2;

	while (nbr > 1)
	{
		while (nbr % i == 0)
		{
			printf("%d", i);
			nbr /= i;
			if(nbr > 1)
				printf("*");
		}
		i++;
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	int nbr = 0;
	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	nbr = atoi(argv[1]);
	printf("%d\n", nbr);
	if (nbr < 0)
		return (printf("\n"), 0);
	if (nbr <= 3)
		printf("%d", nbr);
	else
		calculate(nbr);
	return (0);
}