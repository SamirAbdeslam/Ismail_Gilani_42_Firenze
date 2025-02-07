/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:21:51 by igilani           #+#    #+#             */
/*   Updated: 2025/01/05 19:41:20 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_nbr(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*m;
	int		len;
	long	nb;

	nb = n;
	len = ft_count_nbr (nb);
	m = ft_calloc (len + 1, sizeof(char));
	if (!m)
		return (NULL);
	if (nb < 0)
	{
		m[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		m[0] = '0';
	while (nb != 0)
	{
		m[--len] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (m);
}
