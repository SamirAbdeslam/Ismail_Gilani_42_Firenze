/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:07:59 by igilani           #+#    #+#             */
/*   Updated: 2025/02/23 14:26:46 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	my_pixel_put(int x, int y, t_data *fractal, int color)
{
	int	offset;
	
	offset = (y * fractal->line_length) + (x * (fractal->bits_per_pixel / 8));
	*((unsigned int *)(fractal->addr + offset)) = color;
	print_menu(fractal);
}

static void mandelbrot_or_julia(t_complex *z, t_complex *c, t_data *fractal)
{
	if (ft_strncmp(fractal->title, "julia", 5) == 0)
	{
		c->r = fractal->julia_r;
		c->i = fractal->julia_i;
	}
	else // Mandelbrot
	{
		c->r = z->r;
		c->i = z->i;
	}
}

static void	handle_pixel(int x, int y, t_data *fractal)
{
    t_complex z;
    t_complex c;
    int i;

    i = 0;

	z.r = (map(x, -2, +2, WIDTH) * fractal->zoom) + fractal->offset_x;
	z.i = (map(y, +2, -2, HEIGHT) * fractal->zoom) + fractal->offset_y;

	mandelbrot_or_julia(&z, &c, fractal);

	while(i < fractal->iter)
	{
		z = sum_compl(square_compl(z), c);
		if ((z.r * z.r) + (z.i * z.i) > fractal->hypotenuse)
		{
			fractal->color = map(i, BLACK, WHITE, fractal->iter);
			my_pixel_put(x, y, fractal, fractal->color);
			return;
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

	while(++y < HEIGHT)
	{
		x = -1;
		while(++x < WIDTH)
		{
			handle_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
}

int	print_menu(t_data *data)
{
	int		i;
	char	*str[14];

	mlx_string_put(data->mlx, data->win, 4, 12, 0x00AFAFAF, "COMMANDS:");
	str[0] = "Esc: exit";
	str[1] = "Arrows: move";
	str[2] = "Mouse scroll: zoom";
	str[3] = "+: increase iteration";
	str[4] = "-: decrease iteration";
	i = 1;
	while (++i * 15 <= 150 + 75 * (data->title[0] != 'M'))
		mlx_string_put(data->mlx, data->win, 4, i * 15,
			0x00FFFFFF, str[i - 2]);
	return (0);
}
