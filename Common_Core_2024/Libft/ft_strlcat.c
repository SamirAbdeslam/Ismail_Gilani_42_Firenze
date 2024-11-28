/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmondo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:56:19 by elmondo           #+#    #+#             */
/*   Updated: 2024/11/23 13:56:23 by elmondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*#include <stdio.h>
#include <bsd/string.h>
#include <unistd.h>*/
#include "libft.h"
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j; //Lunghezza dest
	size_t	f; //Lunghezza di src
	f = 0;
	j = 0;
	i = 0;
	// Calcolo la lunghezza di dest fino a size, oltre non DEVE andare
	while (dst[j] != 0 && j < size)
		j++;
	// Strlen di src
	while (src[f] != 0)
		f++;
	// Controllo se la lunghezza di dest e' piu' piccola o uguale a size
	if (size <= j)
		return(j + f);
		//return (size + f);
	// Controllo se la lunghezza di dest e' uguale a size
	if (j == size)
		return (j);
	// Ciclo scorrendo i fino a NULLO e len dest + i(dove siamo adesso) + 1 sono piu' piccoli di size
	while (src[i] != 0 && (j + i + 1) < size)
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	
	return (j + f);
}
/*
int main()
{
	char dest[0xF00] = "there is no stars in the sky";
	char dest2[0xF00] = "there is no stars in the sky";
	char *src = "the cake is a lie !\0I'm hidden lol\r\n";
	size_t max = strlen("the cake is a lie !\0I'm hidden lol\r\n") + strlen("there is no stars in the sky");
	printf("ORIGINALE: %zu\n", ft_strlcat(dest2, src, max));
	printf("MIO: %zu\n", strlcat(dest, src, max));
	printf("\nORIGINALE: %s", dest);
	printf("\nMIO: %s", dest2);
	return (0);
}*/

