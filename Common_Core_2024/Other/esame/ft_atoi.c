/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:43:12 by igilani           #+#    #+#             */
/*   Updated: 2025/03/12 15:56:48 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int i = 0;
	int sign = 1;
	int nbr = 0;
	while (str[i] >= 9 && str[i] <= 13 || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (str[i] >= 0 && str[i] <= 9)
	{
		nbr = 10 * nbr + (str[i] - '0');
		i++;
	}
	return(sign * nbr);
}