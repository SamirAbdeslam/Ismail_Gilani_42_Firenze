/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:24:48 by igilani           #+#    #+#             */
/*   Updated: 2024/05/22 11:24:49 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
/*
int	main()
{
	printf("%d\n", ft_strcmp("Hello", ""));
	printf("%d\n", ft_strcmp("Hestrncmpstrncmpllo", "Hello"));
	printf("%d\n", ft_strcmp("Heo", "Helyu"));
	printf("%d\n", ft_strcmp("Hel", "Heo2"));
}*/
