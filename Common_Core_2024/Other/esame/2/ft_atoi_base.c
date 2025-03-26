/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:47:44 by igilani           #+#    #+#             */
/*   Updated: 2025/03/19 10:59:36 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_atoi_base(const char *str, int str_base)
{
	int i = 0;
	int sign = 1;
	if (str_base < 2 || str_base > 16)
		return(0);
	while (str[i] >= 9 && (str[i] <= 13 || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if(str[i] == '-')
			sign *= -1;
		i++;
	}
	int nbr = 0;
	while(str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			nbr = nbr * str_base + str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F')
			nbr = nbr * str_base + str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			nbr = nbr * str_base + str[i] - 'a' + 10;
		else
			return(sign * nbr);
		i++;
	}
	return(sign * nbr);
}

int main()
{
	printf("%d", ft_atoi_base("12fdb3", 16));
}