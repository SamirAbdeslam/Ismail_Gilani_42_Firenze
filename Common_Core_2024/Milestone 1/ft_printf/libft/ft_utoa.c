/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:52:35 by igilani           #+#    #+#             */
/*   Updated: 2025/01/10 17:06:45 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_nbr(unsigned long int n)
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

char	*ft_utoa(unsigned long int n)
{
	int		len;
	char	*m;

	len = ft_count_nbr(n);
	m = ft_calloc (len + 1, sizeof(char));
	if (!m)
		return (NULL);
	if (n == 0)
		m[0] = '0';
	while (n != 0)
	{
		m[--len] = n % 10 + '0';
		n = n / 10;
	}
	return (m);
}
