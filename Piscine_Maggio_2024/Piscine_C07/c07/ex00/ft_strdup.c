/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:41:51 by igilani           #+#    #+#             */
/*   Updated: 2024/05/30 11:41:52 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *src)
{
	int	i;
	
	i = 0;
	
	while(src[i] != '\0')
	{
		i++;
	}
	return(i);
}

char	*ft_strdup(char *src)
{
	char	*str;
	int	i;

	i = ft_strlen(src);
	
	str = (char*) malloc((i + 1) * sizeof(char));
	
	i = 0;
	
	if(str == (char*)0)
	{
		return((char*)0);
	}
	
	while(src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	return(str);
	
	free(str);
}

int main(int argc, char *argv[])
{
	int	i;
	char	*str;
	
	i = 0;
	if(argc)
	{
		str = ft_strdup(&argv[1][0]);
		write(1, str, 4);
	}
}
