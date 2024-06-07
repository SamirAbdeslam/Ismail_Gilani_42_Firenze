/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:07:15 by igilani           #+#    #+#             */
/*   Updated: 2024/06/05 18:07:16 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	len;

	len = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[len + i] = src[i];
		i++;
	}
	dest[len + i] = '\0';
	return (dest);
}

char *ft_strjoin(int size, char **strs, char *sep)
{
	int	i;
	char	*arr;

	size = 0;
	i = size;
	arr = (char *)malloc(size * sizeof(char));
	while(i > 0)
	{
		arr = ft_strcat(strs[size], sep);
		size++;
		i--;
	}
	return(arr);
}

int main()
{
	printf("%s",ft_strjoin(2, "ciao", "c");
}

/*Passare una matrice come input e poi far scorrere ogni stringa nella matrice fino al carattere nullo e utilizzare strcat per inserire il carattere separatore 
Size e' la grandezza effettiva dell'array */
