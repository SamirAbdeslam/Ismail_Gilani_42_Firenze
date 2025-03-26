/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramsum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:44:06 by igilani           #+#    #+#             */
/*   Updated: 2025/03/19 14:50:21 by igilani          ###   ########.fr       */
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

int main(int argc, char **argv)
{
	(void)argv;
	int i = 0;
	if (argc == 1)
	{
		write(1, "0\n", 2);
		return(0);
	}
	while (--argc)
		i++;
	ft_putnbr(i);
	write(1, "\n", 1);
	return(0);
}