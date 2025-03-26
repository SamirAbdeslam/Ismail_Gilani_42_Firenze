/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:54:13 by igilani           #+#    #+#             */
/*   Updated: 2025/03/18 16:01:37 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	max(int *tab, unsigned int len)
{
	int max = 0;
	int i = 0;

	while (len > 0)
	{
		if (tab[i] > max)
			max = tab[i];
		i++;
		len--;
	}
	return(max);
}

int main()
{
	int tab[] = {1, 2, 3, 4, 5, 30, 6, 88, 90, 21, 11, 8, 9, 44, 10854, 23456, 3247, 0};
	int len = 19;

	printf("%d\n", max(tab, len));
}