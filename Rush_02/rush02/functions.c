/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:34:34 by igilani           #+#    #+#             */
/*   Updated: 2024/06/02 23:34:35 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ft.h"

unsigned long int	ft_atoi(const char *str)
{
	unsigned long int	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}

char	*ft_strdup(char *src)
{
	char	*strdup;
	int		i;

	strdup = (char *) malloc ((sizeof (char) * 1000));
	i = 0;
	while (src[i])
	{
		strdup[i] = src[i];
		i++;
	}
	strdup[i] = '\0';
	return (strdup);
}

int	error(int num_error)
{
	if (num_error == 1)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	else if (num_error == 2)
	{
		write(1, "DictError\n", 10);
		return (0);
	}
	return (0);
}
