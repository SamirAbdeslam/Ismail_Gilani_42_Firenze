/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:24:59 by igilani           #+#    #+#             */
/*   Updated: 2024/11/29 10:28:14 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	t;
	int				i;

	i = 0;
	t = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == t)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (s[i] == t)
		return ((char *)&s[i]);
	return (NULL);
}
