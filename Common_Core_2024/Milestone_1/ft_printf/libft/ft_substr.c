/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:13:12 by igilani           #+#    #+#             */
/*   Updated: 2024/12/31 13:13:56 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ss;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(&s[start]) > len)
	{
		ss = malloc(len + 1);
		if (!ss)
			return (NULL);
		ft_strlcpy(ss, s + start, len + 1);
	}
	else
	{
		ss = malloc(ft_strlen(&s[start]) + 1);
		if (!ss)
			return (NULL);
		ft_strlcpy(ss, s + start, ft_strlen(&s[start]) + 1);
	}
	return (ss);
}
