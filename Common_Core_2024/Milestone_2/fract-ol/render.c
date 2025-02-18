/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:07:59 by igilani           #+#    #+#             */
/*   Updated: 2025/02/18 19:40:16 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	my_pixel_put(int x, int y, t_data *img, int color)
{
	int	offset;

	offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
	*(unsigned int *)(img->addr + offset) = color;
}

static void	handle_pixel(int x, int y, t_data *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;

	i = 0;
	z.r = 0.0;
	z.i = 0.0;

	c.r = map(x, -2, +2, WIDTH);
	c.i = map(y, +2, -2, HEIGHT);

	while(i < fractal->iter)
	{
		z = sum_compl(square_compl(z), c);
		if ((z.r * z.r) + (z.i * z.i) > fractal->hypotenuse)
		{
			fractal->color = map(i, BLACK, WHITE, fractal->iter);
			my_pixel_put(x, y, fractal->img, fractal->color);
			return;
		}
		++i;
	}
	my_pixel_put(x, y, fractal->img, ELETRIC_BLUE);
}

void	fractal_render(t_data *fractal)
{
	int	x;
	int	y;

	y = -1;

	while(--y < HEIGHT)
	{
		x = -1;
		while(--x < WIDTH)
		{
			handle_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}