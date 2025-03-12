/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr&ft_putnbr_base.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:42 by igilani           #+#    #+#             */
/*   Updated: 2025/03/12 18:25:39 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void ft_putnbr(int nbr)
{
	if (nbr == INT_MIN)
	{
		write(1, "-2", 2);
		ft_putnbr(147483648);
	}
	else if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
		ft_putnbr(nbr);
	}
	else if (nbr >= 0 && nbr <= 9)
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

void ft_putnbr_base(int nbr, char *base)
{
	if (nbr >= 16)
		ft_putnbr_base(nbr / 16, base);
	write (1, &base[nbr % 16], 1);
}

int main(int argc, char **argv)
{
	(void)argc;
	ft_putnbr(atoi(argv[1]));
	write(1, "\n", 1);
	ft_putnbr_base(atoi(argv[1]), "0123456789abcdef");
}
