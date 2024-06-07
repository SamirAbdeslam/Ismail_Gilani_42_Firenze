/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:23:06 by igilani           #+#    #+#             */
/*   Updated: 2024/05/28 16:23:07 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <unistd.h>
#include <stdio.h>*/

int	ft_atoi(char *str)
{
	int	i;
	int	n;
	int	sign;

	i = 0;
	n = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	while ((str[i] == 43 || str[i] == 45))
	{
		if (str[i] == 43)
		{
			sign *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = 10 * n + (str[i] - '0');
		i++;
	}
	return (sign * n);
}
/*
int main()
{
	char a[] = "  ----+--+1234ab567";
	int result = ft_atoi(a);
	printf("%d", result);
}*/
