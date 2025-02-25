/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:44:01 by igilani           #+#    #+#             */
/*   Updated: 2025/02/25 12:47:49 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	handle_error(void)
{
	perror ("Errore con il malloc");
	exit (EXIT_FAILURE);
}

void	data_init(t_data *fractal)
{
	fractal->hypotenuse = 4;
	fractal->iter = 42;
	fractal->zoom = 1.0;
	fractal->offset_x = 0.0;
	fractal->offset_y = 0.0;
}

void	fractal_init(t_data *fractal)
{
	fractal->mlx = mlx_init();
	if (NULL == fractal->mlx)
		handle_error();
	fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, fractal->title);
	if (NULL == fractal->win)
	{
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
		handle_error();
	}
	fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (NULL == fractal->img)
	{
		mlx_destroy_window(fractal->mlx, fractal->win);
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
		handle_error();
	}
	fractal->addr = mlx_get_data_addr(fractal->img,
			&fractal->bits_per_pixel,
			&fractal->line_length,
			&fractal->endian);
	events_init(fractal);
	data_init(fractal);
}

int	main(int argc, char **argv)
{
	t_data	fractal;

	fractal = (t_data){0};
	if ((2 == argc && !ft_strncmp(argv[1], "mandelbrot", 10))
		|| (4 == argc && !ft_strncmp(argv[1], "julia", 5))
		|| (2 == argc && !ft_strncmp(argv[1], "tricorn", 7)))
	{
		fractal.title = argv[1];
		if (!ft_strncmp(fractal.title, "julia", 5))
		{
			fractal.julia_r = ft_atodbl(argv[2]);
			fractal.julia_i = ft_atodbl(argv[3]);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx);
	}
	else
	{
		ft_putstr_fd(M, 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}
