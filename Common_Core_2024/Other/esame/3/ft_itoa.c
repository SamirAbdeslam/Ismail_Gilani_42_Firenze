/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:40:07 by igilani           #+#    #+#             */
/*   Updated: 2025/03/19 18:13:46 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int	recursive(long n, char *m, int i)
{
	if (n >= 0 && n <= 9)
	{
		m[i] = n + '0';
		return (i + 1);
	}
	else
	{
		i = recursive(n / 10, m, i);
		i = recursive(n % 10, m, i);
	}
	return (i);
}

char	*ft_itoa(int nbr)
{
	int i = 0;
	char *m = (char *)malloc(30 * sizeof(char));
	long int n;

	n = nbr;
	if(n < 0)
	{
		m[0] = '-';
		n *= -1;
		i++;
	}
	m[recursive(n, m, i)] = '\0';
	return (m);
}

int main()
{
	printf("|%s|\n", ft_itoa(INT_MAX));
}