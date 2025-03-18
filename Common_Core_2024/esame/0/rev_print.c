/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:32:42 by igilani           #+#    #+#             */
/*   Updated: 2025/03/17 14:36:13 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int i = 0;
	if (argc != 2)
	{
		write(1, "\n", 1);
		return(0);
	}
	while(argv[1][i] != '\0')
		i++;
	i--;
	while (i >= 0)
	{
		write(1, &argv[1][i], 1);
		i--;
	}
	write(1, "\n", 1);
	return(0);
}