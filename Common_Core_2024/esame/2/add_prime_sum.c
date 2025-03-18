/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:03:51 by igilani           #+#    #+#             */
/*   Updated: 2025/03/18 18:36:37 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int prime(int nbr)
{
	int i = 2;
	int save = 0;

	while (nbr > 2)
	{
		if (nbr % i != 0)
		{
			save += nbr;
		}
		nbr--;
	}
	return(save + 2);
}

int ft_atoi(char *str)
{
	int i = 0;
	int nbr = 0;
	
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (10 * nbr) + (str[i] - '0');
		i++;
	}
	return(nbr);
}

void ft_putnbr(int nbr)
{
	if (nbr >= 0 && nbr <= 9)
	{
		nbr += '0';
		write(1, &nbr, 1);
	}
	else
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
		
}

int main(int argc, char **argv)
{
	if (argc != 2 || argv[1][0] == '-')
	{
		write(1, "0\n", 2);
		return(0);
	}
	int nbr = ft_atoi(argv[1]);
	ft_putnbr(prime(nbr));
	return(0);
}