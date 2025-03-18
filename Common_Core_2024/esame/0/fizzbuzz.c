/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzbuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:53:42 by igilani           #+#    #+#             */
/*   Updated: 2025/03/17 14:11:22 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void ft_putnbr (int i)
{
	if (i >= 0 && i <= 9)
	{
		i = i + '0';
		write(1, &i, 1);
	}
	else
	{
		ft_putnbr(i / 10);
		ft_putnbr(i % 10);
	}
}

int main ()
{
	int i = 1;

	while (i < 100)
	{
		if (i % 3 == 0 && i % 5 != 0)
			write(1, "fizz", 4);
		else if (i % 5 == 0 && i % 3 != 0)
			write(1, "buzz", 4);
		else if (i % 3 == 0 && i % 5 == 0)
			write(1, "fizzbuzz", 8);
		else
			ft_putnbr(i);
		write(1, "\n", 1);
		i++;
	}
	return(0);
}