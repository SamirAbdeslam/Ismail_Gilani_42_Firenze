/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:43:47 by igilani           #+#    #+#             */
/*   Updated: 2024/06/03 15:43:47 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include<stdio.h>
#include<stdlib.h>*/

int	ft_iterative_factorial(int nb)
{
	int	result;

	result = 1;
	if (nb < 0)
	{
		return (0);
	}
	while (nb > 1)
	{
		result *= nb;
		nb--;
	}
	return (result);
}
/*
int main(int argc, char **argv)
{
	int	result;
	
	if(argc)
	{
		result = atoi(argv[1]);
		printf("%d", ft_iterative_factorial(result));
	}
}*/
