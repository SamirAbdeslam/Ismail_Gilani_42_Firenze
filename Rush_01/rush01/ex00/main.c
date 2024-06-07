/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:14:20 by igilani           #+#    #+#             */
/*   Updated: 2024/05/26 19:14:22 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	error(void)
{
	write(1, "Error!\n", 7);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	print_matrix(int matrix[4][4])
{
	int	x;
	int	y;

	x = 0;
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			ft_putchar(matrix[x][y]);
			if (y < 4 - 1)
				ft_putchar(' ');
			y++;
		}
		ft_putchar('\n');
		x++;
	}
}

void	ceck(char *argv[])
{
	int	i;
	int	x;
	int	y;
	int	matrix[4][4];

	i = 0;
	x = 0;
	while (argv[1][i] != '\0')
	{
		y = 0;
		while (y < 4)
		{
			if (argv[1][i] >= '0' && argv[1][i] <= '4')
			{
				matrix[x][y] = argv[1][i];
				y++;
			}
			i++;
		}
		x++;
	}
	if (i % 4 == 0)
		error();
	else
		print_matrix(matrix);
}

int	main(int argc, char *argv[])
{
	if (argc <= 2)
		ceck(argv);
	else
		error();
}
