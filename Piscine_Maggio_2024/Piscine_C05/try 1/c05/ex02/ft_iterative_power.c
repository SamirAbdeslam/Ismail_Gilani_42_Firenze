/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:31:07 by igilani           #+#    #+#             */
/*   Updated: 2024/06/03 18:31:08 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include<stdio.h>
#include<stdlib.h>*/

int	ft_iterative_power(int nb, int power)
{
	int	result;
	int	i;

	result = 1;
	i = power;
	if (power == 0)
	{
		return (1);
	}
	if (power == 1)
	{
		return (nb);
	}
	while (i != 0)
	{
		result *= nb;
		i--;
	}
	return (result);
}
/*
int main(int argc, char **argv)
{
	if(argc)
	{
		printf("%d", ft_iterative_power(atoi(argv[1]),atoi(argv[2])));
	}
}*/
