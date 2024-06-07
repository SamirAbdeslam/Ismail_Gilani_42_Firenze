/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:41:52 by igilani           #+#    #+#             */
/*   Updated: 2024/05/23 15:41:53 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && (s1[i] != '\0' && s2[i] != '\0'))
	{
		if (s1[i] > s2[i])
		{
			return (1);
		}
		else if (s1[i] < s2[i])
		{
			return (-1);
		}
		i++;
	}
	if (s1[i] != s2[i])
	{
		return (s1[i] - s2[i]);
	}
	return (0);
}
/*
int	main()
{
	printf("%d\n", ft_strncmp("Hello2", "Hello",5));
	printf("%d\n", ft_strncmp("Hestrncmpstrncmpllo", "Hello", 15));
	printf("%d\n", ft_strncmp("Heo", "Helyu", 15));
	printf("%d\n", ft_strncmp("Hel", "Heo2", 15));
}*/
