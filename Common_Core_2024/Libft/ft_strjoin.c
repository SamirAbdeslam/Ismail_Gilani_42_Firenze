/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:25:50 by igilani           #+#    #+#             */
/*   Updated: 2024/11/29 11:32:54 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ns;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ns = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ns)
		return (NULL);
	while (s1[i] != '\0')
	{
		ns[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ns[i] = s2[j];
		i++;
		j++;
	}
	ns[i] = '\0';
	return (ns);
}
