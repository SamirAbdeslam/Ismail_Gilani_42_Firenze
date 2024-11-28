/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:13:22 by igilani           #+#    #+#             */
/*   Updated: 2024/06/03 18:13:23 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include<stdio.h>
#include<stdlib.h>*/

int	ft_recursive_factorial(int nb)
{
	int	result;

	result = 1;
	if (nb < 0)
	{
		return (0);
	}
	if (nb > 1)
	{
		result = nb * (ft_recursive_factorial(nb - 1));
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
		printf("%d", ft_recursive_factorial(result));
	}
}*/
