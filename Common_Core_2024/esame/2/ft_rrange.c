/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:33:44 by igilani           #+#    #+#             */
/*   Updated: 2025/03/19 12:45:24 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	*ft_rrange(int start, int end)
{
	int tmp = start;
	int i = 0;

	if (start < end)
	{
		while(tmp < end)
		{
			tmp++;
			i++;
		}
		i++;
	}
	else
	{
		while(tmp > end)
		{
			tmp--;
			i++;
		}
		i++;
	}
	int *m = (int *)malloc(i * sizeof(int));
	if (!m)
		return(0);
	if (start < end)
	{
		i = 0;
		while(end >= start)
		{
			m[i] = end;
			end--;
			i++;
		}
	}
	else
	{
		i = 0;
		while(start >= end)
		{
			m[i] = end;
			end++;
			i++;
		}
	}
	return(m);
}

int main()
{
	int i = 0;
	int *arr = ft_rrange(0, -3);
	int arr_len = abs(0 - -3);
	while(i <= arr_len)
	{
		printf("%d ", arr[i]);
		i++;
	}
}