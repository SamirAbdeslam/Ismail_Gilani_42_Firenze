/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:29:11 by igilani           #+#    #+#             */
/*   Updated: 2025/03/19 15:41:25 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void ft_putnbr_base(int nbr, char *base)
{
	if (nbr >= 16)
		ft_putnbr_base(nbr / 16, base);
	write(1, &base[nbr % 16], 1);
}

int ft_atoi(char *str)
{
	int i = 0;
	int nbr = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = 10 * nbr + (str[i] - '0');
		i++;
	}
	return(nbr);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(1, "\n", 1);
		return(0);
	}
	ft_putnbr_base(ft_atoi(argv[1]), "0123456789abcdef");
	write(1, "\n", 1);
	return(0);
}