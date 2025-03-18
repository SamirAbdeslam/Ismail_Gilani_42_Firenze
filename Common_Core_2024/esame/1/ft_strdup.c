/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:44:32 by igilani           #+#    #+#             */
/*   Updated: 2025/03/17 18:50:27 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ft_strlen(char *src)
{
	int i = 0;
	while(src[i])
		i++;
	return(i);
}

char	*ft_strdup(char *src)
{
	int i = 0;
	char *m = (char *)malloc(ft_strlen(src) * sizeof(char));

	while(src[i])
	{
		m[i] = src[i];
		i++;
	}
	return(m);
}

int main()
{
	char *src = "Cacato nel puzzo";

	printf("%s\n", ft_strdup(src));
	printf("%s\n", strdup(src));
}