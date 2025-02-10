/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:15:58 by igilani           #+#    #+#             */
/*   Updated: 2025/02/10 17:04:09 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// int close_window(void *param)
// {
// 	(void)param;
// 	exit(0);
// }

// int	key_hook(int keycode, t_data data)
// {
// 	if (keycode == KEY_ESC)
// 		close_window(&data.win);
// 	// if (keycode == KEY_PLUS)
// 	// 	data.max_iter += 10;
// 	// if (keycode == KEY_MINUS)
// 	// 	data.max_iter -= 10;
// 	// render_fractal(data); // Funzione di ridisegno
// 	return (0);
// }

void	usage(int argc, char **argv)
{
	if((2 == argc && !ft_strncmp(argv[1], "mandelbrot", 10)) || (4 == argc && !ft_strncmp(argv[1], "julia", 5)))
	{
		return;
	}
	else
	{
		ft_putstr_fd("Usage: ./fractol mandelbrot or julia 'value 1' 'value 2'\n", 2);
		exit(EXIT_FAILURE);
	}
}
	
int main(int argc, char **argv)
{
	//usage(argc, argv);
	// t_data	data;
	// int		y;
	// int		x;
	// int		offset;
	int		i = 0;
	(void)argc;
	t_complex z;
	t_complex c; //punto specifico del frattale
	double temp;

	z.r = 0;
	z.i = 0;

	c.r = atof(argv[1]);
	c.i = atof(argv[2]);

	while(i < ft_atoi(argv[3]))
	{
		temp = (z.r * z.r) - (z.i * z.i);
		
		z.i = 2 * z.r * z.i;
		z.r = temp;

		z.r += c.r;
		z.i += c.i;

		printf("Iterazione ->%d: Reale = %f, Immaginario = %f\n", i, z.r, z.i);
		i++;
	}

	// data.mlx = mlx_init();
	// data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Fractol");
	// data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	// char *buffer = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	

	// mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	// mlx_key_hook(data.win, key_hook, &data);
	// mlx_hook(data.win, 17, 0, close_window, NULL);
	// mlx_loop(data.mlx);
	return (0);
}