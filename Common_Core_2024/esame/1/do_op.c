/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:43:05 by igilani           #+#    #+#             */
/*   Updated: 2025/03/17 17:48:33 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		write(1, "\n", 1);
		return(0);
	}
	int n1 = atoi(argv[1]);
	int n2 = atoi(argv[3]);
	int i = 0;
	
	if (argv[2][i] == '+')
		printf("%d\n", n1 + n2);
	else if (argv[2][i] == '-')
		printf("%d\n", n1 - n2);
	else if (argv[2][i] == '*')
		printf("%d\n", n1 * n2);
	else if (argv[2][i] == '/')
		printf("%d\n", n1 / n2);
	else if (argv[2][i] == '%')
		printf("%d\n", n1 % n2);
	return(0);
}