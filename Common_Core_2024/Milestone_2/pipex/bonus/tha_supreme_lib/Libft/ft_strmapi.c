/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:30:13 by igilani           #+#    #+#             */
/*   Updated: 2024/12/10 16:33:02 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*m;

	i = 0;
	m = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!m)
		return (NULL);
	while (s[i] != '\0')
	{
		m[i] = f(i, s[i]);
		i++;
	}
	return (m);
}
