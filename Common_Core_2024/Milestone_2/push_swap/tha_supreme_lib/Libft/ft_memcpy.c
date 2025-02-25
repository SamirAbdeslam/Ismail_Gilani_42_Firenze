/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:21:00 by igilani           #+#    #+#             */
/*   Updated: 2024/12/05 18:13:43 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!src && !dest)
	{
		return (NULL);
	}
	while (i < n)
	{
		((unsigned char *) dest)[i] = ((const char *) src)[i];
		i++;
	}
	return (dest);
}
/*
int main()
{
	char dest[20]="";
	char src[20]="Hello World";
	size_t n = 5;

	printf("%s", (char *)ft_memcpy(dest,src,n));
	return(0);
}
*/
