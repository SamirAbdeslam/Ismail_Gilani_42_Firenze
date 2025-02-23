/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:15:58 by igilani           #+#    #+#             */
/*   Updated: 2025/02/23 14:25:15 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int close_window(t_data *fractal)
{
    mlx_destroy_image(fractal->mlx, fractal->img);
    mlx_destroy_window(fractal->mlx, fractal->win);
    mlx_destroy_display(fractal->mlx);
    free(fractal->mlx);
    exit(EXIT_SUCCESS);
}

int	key_hook(int keysym, t_data *fractal)
{
    if (keysym == XK_Escape)
        close_window(fractal);
    else if (keysym == XK_Up)
        fractal->offset_y += (0.5 * fractal->zoom);
    else if (keysym == XK_Down)
        fractal->offset_y -= (0.5 * fractal->zoom);
    else if (keysym == XK_Left)
        fractal->offset_x -= (0.5 * fractal->zoom);
    else if (keysym == XK_Right)
        fractal->offset_x += (0.5 * fractal->zoom);
    else if (keysym == XK_plus || keysym == XK_equal)
        fractal->iter += 10;
    else if (keysym == XK_minus)
       fractal->iter -= 10;
    fractal_render(fractal);
    return (0);
}
// int mouse_pointer_hook(int x, int y, t_data *fractal)
// {
//     fractal->c.r = (map(x, -2, +2, WIDTH) * fractal->zoom) + fractal->offset_x;
//     fractal->c.i = (map(y, +2, -2, HEIGHT) * fractal->zoom) + fractal->offset_y;
//     fractal_render(fractal);
//     return(0);
// }

int mouse_hook(int button, int x, int y, t_data *fractal)
{
    (void)x;
    (void)y;
    if(button == Button4)
    {
        fractal->zoom *= 0.95;
    }
    else if (button == Button5)
    {
        fractal->zoom *= 1.05;
    }
    fractal_render(fractal);
    return(0);
}


static void events_init(t_data *fractal)
{
    mlx_hook(fractal->win, KeyPress, KeyPressMask, key_hook, fractal);
    mlx_hook(fractal->win, ButtonPress, ButtonPressMask, mouse_hook, fractal);
    // mlx_hook(fractal->win, MotionNotify, PointerMotionMask, mouse_pointer_hook, fractal);
    mlx_hook(fractal->win, DestroyNotify, StructureNotifyMask, close_window, fractal);
}

void data_init(t_data *fractal)
{
    fractal->hypotenuse = 4;
    fractal->iter = 42;
    fractal->zoom = 1.0;      // Valore di default
    fractal->offset_x = 0.0;  // Centrato sull'asse X
    fractal->offset_y = 0.0;  // Centrato sull'asse Y
}

static void	handle_error(void)
{
    perror("Errore con il malloc");
    exit(EXIT_FAILURE);
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
    fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bits_per_pixel, &fractal->line_length, &fractal->endian);
        
    events_init(fractal);
    data_init(fractal);
}

int main(int argc, char **argv)
{
    t_data fractal = {0};

    if ((2 == argc && !ft_strncmp(argv[1], "mandelbrot", 10)) || 
        (4 == argc && !ft_strncmp(argv[1], "julia", 5)))
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
        ft_putstr_fd("Usage: ./fractol mandelbrot or julia 'value 1' 'value 2'\n", 2);
        exit(EXIT_FAILURE);
    }
}
