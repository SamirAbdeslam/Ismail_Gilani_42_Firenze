/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:26:47 by igilani           #+#    #+#             */
/*   Updated: 2024/11/29 10:26:48 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	const void	*mem;

	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	ft_bzero ((char *)mem, nmemb * size);
	return ((char *)mem);
}
