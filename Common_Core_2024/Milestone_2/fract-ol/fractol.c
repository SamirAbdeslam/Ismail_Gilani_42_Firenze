/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:15:58 by igilani           #+#    #+#             */
/*   Updated: 2025/02/21 19:14:07 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int close_window(void *param)
{
    (void)param;
    exit(0);
}

int	key_hook(int keycode, t_data *data)
{
	printf("%d\n", keycode);
    if (keycode == XK_Escape)
        close_window(data->win);
    return (0);
}

void data_init(t_data *fractal)
{
    fractal->hypotenuse = 4;
    fractal->iter = 42;
    fractal->zoom = 1.0;      // Valore di default
    fractal->offset_x = 0.0;  // Centrato sull'asse X
    fractal->offset_y = 0.0;  // Centrato sull'asse Y
}

void	handle_error()
{
    perror("Errore con il malloc");
    exit(EXIT_FAILURE);
}

void	fractal_init(t_data *fractal)
{
    fractal->mlx = mlx_init();
    if (!fractal->mlx)
    {
        handle_error();
    }
    fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, fractal->title);
    if (!fractal->win)
    {
        mlx_destroy_display(fractal->mlx);
        free(fractal->mlx);
        handle_error();
    }
    fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
    if (!fractal->img)
    {
        mlx_destroy_window(fractal->mlx, fractal->win);
        mlx_destroy_display(fractal->mlx);
        free(fractal->mlx);
        handle_error();
    }
    fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bits_per_pixel, &fractal->line_length, &fractal->endian);
        
    data_init(fractal);
}

int main(int argc, char **argv)
{
    t_data fractal = {0}; // Inizializza tutti i campi a 0/NULL

    if ((2 == argc && !ft_strncmp(argv[1], "mandelbrot", 10)) || 
        (4 == argc && !ft_strncmp(argv[1], "julia", 5)))
    {
        fractal.title = argv[1];
        if (4 == argc && !ft_strncmp(argv[1], "julia", 5))
        {
            fractal.julia_r = atof(argv[2]);
            fractal.julia_i = atof(argv[3]);
        }
        fractal_init(&fractal);
        fractal_render(&fractal);
        mlx_key_hook(fractal.win, key_hook, &fractal);
        mlx_hook(fractal.win, 17, 0, close_window, &fractal); // Aggiungi hook per la chiusura
        mlx_loop(fractal.mlx);
    }
    else
    {
        ft_putstr_fd("Usage: ./fractol mandelbrot or julia 'value 1' 'value 2'\n", 2);
        exit(EXIT_FAILURE);
    }
    return (0);
}
