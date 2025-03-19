/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:51:44 by igilani           #+#    #+#             */
/*   Updated: 2025/03/19 17:06:29 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void ft_putnbr(int nbr)
{
	if (nbr >= 0 && nbr <= 9)
	{
		nbr = nbr + '0';
		write(1, &nbr, 1);
	}
	else
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
}

int ft_atoi(char *str)
{
	int i = 0;
	int nbr = 0;

	while(str[i] >= '0' && str[i] <= '9')
	{
		nbr = 10 * nbr + (str[i] - '0');
		i++;
	}
	return(nbr);
}

int main(int argc, char **argv)
{
	int i = 1;
	
	if (argc == 1)
	{
		write(1, "\n", 1);
		return(0);
	}
	int nbr = ft_atoi(argv[1]);

	while(i <= 9)
	{
		ft_putnbr(i);
		write(1, " x ", 3);
		ft_putnbr(nbr);
		write(1, " = ", 3);
		ft_putnbr(nbr * i);
		write(1, "\n", 1);
		i++;
	}
	return(0);
}