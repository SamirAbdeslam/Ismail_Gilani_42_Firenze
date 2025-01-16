/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:26:15 by igilani           #+#    #+#             */
/*   Updated: 2025/01/16 20:58:04 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*mem;

	mem = ft_calloc(ft_strlen(s) + 1, 1);
	if (!mem)
		return (NULL);
	ft_strlcpy (mem, s, ft_strlen(s) + 1);
	return (mem);
}
