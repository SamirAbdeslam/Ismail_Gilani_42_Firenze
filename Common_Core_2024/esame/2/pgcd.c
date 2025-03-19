/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pgcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:52:04 by igilani           #+#    #+#             */
/*   Updated: 2025/03/19 15:03:35 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc != 3)
		return(printf("\n"), 0);
	
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);

	if (a == 0 || b == 0)
		return(0);
	unsigned int n;

	if (a < b)
		n = a;
	else
		n = b;
	while (n > 1)
	{
		if (a % n == 0 && b % n == 0)
			return(printf("%d\n", n), 0);
		n--;
	}
	return(printf("%d\n", n), 0);
}