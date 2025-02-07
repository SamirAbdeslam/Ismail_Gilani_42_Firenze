/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:25:15 by igilani           #+#    #+#             */
/*   Updated: 2024/11/29 10:25:16 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	t;
	int				i;

	i = ft_strlen(s);
	t = (unsigned char)c;
	while (i)
	{
		if (s[i] == t)
		{
			return ((char *)&s[i]);
		}
		i--;
	}
	if (s[i] == t)
		return ((char *)&s[i]);
	return (NULL);
}
