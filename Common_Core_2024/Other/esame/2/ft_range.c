/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:20:47 by igilani           #+#    #+#             */
/*   Updated: 2025/03/19 12:39:44 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int *ft_range(int start, int end)
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
		i += 1;
	}
	else
	{
		while(tmp > end)
		{
			tmp--;
			i++;
		}
		i += 1;
	}
	int *m = (int *)malloc(i  * sizeof(int));
	if (!m)
		return(0);
	i--;
	if (start < end)
	{
		while (end >= start)
		{
			m[i] = end;
			i--;
			end--;
		}
	}
	else
	{
		while (start >= end)
		{
			m[i] = end;
			i--;
			end++;
		}
	}
	return(m);
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	int	arr_len;
// 	int	*arr;

//  arr_len = abs(atoi(argv[2]) - atoi(argv[1]));
// 	arr = ft_range(atoi(argv[1]), atoi(argv[2]));
// 	for (int i = 0; i <= arr_len; i += 1)
// 		printf("%d ", arr[i]);
// 	free(arr);
// 	return (EXIT_SUCCESS);
// }

int main()
{
	int i = 0;
	int *arr = ft_range(-1, 2);
	int arr_len = abs(-1 - 2);
	while(i <= arr_len)
	{
		printf("%d ", arr[i]);
		i++;
	}
}