/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprime.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:20:29 by igilani           #+#    #+#             */
/*   Updated: 2025/03/19 17:39:22 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void calcola(int nbr)
{
	int i = 2;

	while (nbr > 1)
	{
		while (nbr % i == 0)
		{
			printf("%d", i);
			nbr /= i;
			if (nbr > 1)
				printf("*");
		}
		i++;
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(1, "\n", 1);
		return(0);
	}
	int nbr = atoi(argv[1]);
	if(nbr < 0)
		return(printf("\n"), 0);
	if (nbr <= 3)
		printf("%d", nbr);
	else
		calcola(nbr);
	return(0);
}
