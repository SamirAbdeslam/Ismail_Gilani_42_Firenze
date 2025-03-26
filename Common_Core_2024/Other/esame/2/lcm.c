/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:57:01 by igilani           #+#    #+#             */
/*   Updated: 2025/03/19 14:43:34 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int    lcm(unsigned int a, unsigned int b)
{
	if (a == 0 || b == 0)
		return(0);
	unsigned int n;

	if (a > b)
		n = a;
	else
		n = b;

	while (1)
	{
		if (n % a == 0 && n % b == 0)
			return(n);
		++n;
	}
}

#include <stdio.h>

int main(void)
{
	printf("%u\n", lcm(5, 2));
}