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

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
/*
int	main()
{
	printf("%d\n", ft_strncmp("Hello", "Hello",6));
	printf("%d\n", ft_strncmp("Hestrncmpstrncmpllo", "Hello", 15));
	printf("%d\n", ft_strncmp("Heo", "Helyu", 15));
	printf("%d\n", ft_strncmp("Hel", "Heo2", 15));
}*/
