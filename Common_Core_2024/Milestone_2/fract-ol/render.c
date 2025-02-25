/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:43:54 by igilani           #+#    #+#             */
/*   Updated: 2025/02/25 12:46:37 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map(double unscaled_num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * ((unscaled_num - 0)
			/ (old_max - 0)) + new_min);
}

static void	my_pixel_put(int x, int y, t_data *fractal, int color)
{
	int	offset;

	offset = (y * fractal->line_length) + (x * (fractal->bits_per_pixel / 8));
	*((unsigned int *)(fractal->addr + offset)) = color;
}

void	fractal_set(t_complex *z, t_complex *c, t_data *fractal)
{
	if (ft_strncmp(fractal->title, "julia", 5) == 0)
	{
		c->r = fractal->julia_r;
		c->i = fractal->julia_i;
	}
	else
	{
		c->r = z->r;
		c->i = z->i;
	}
}

void	handle_pixel(int x, int y, t_data *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;

	i = 0;
	z.r = (map(x, -2, +2, WIDTH) * fractal->zoom) + fractal->offset_x;
	z.i = (map(y, +2, -2, HEIGHT) * fractal->zoom) + fractal->offset_y;
	fractal_set(&z, &c, fractal);
	while (i < fractal->iter)
	{
		if (ft_strncmp(fractal->title, "tricorn", 7) == 0)
			z.i = -z.i;
		z = sum_compl(square_compl(z), c);
		if ((z.r * z.r) + (z.i * z.i) > fractal->hypotenuse)
		{
			fractal->color = map(i, BLACK, WHITE, fractal->iter);
			my_pixel_put(x, y, fractal, fractal->color);
			return ;
		}
		++i;
	}
	my_pixel_put(x, y, fractal, ELETRIC_BLUE);
}

void	fractal_render(t_data *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			handle_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	print_menu(fractal);
}
