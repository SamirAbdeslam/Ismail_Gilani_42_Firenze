/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:15:29 by igilani           #+#    #+#             */
/*   Updated: 2024/12/05 18:15:33 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	f;

	f = 0;
	j = 0;
	i = 0;
	while (dst[j] != 0 && j < size)
		j++;
	while (src[f] != 0)
		f++;
	if (size <= j)
		return (j + f);
	if (j == size)
		return (j);
	while (src[i] != 0 && (j + i + 1) < size)
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (j + f);
}
