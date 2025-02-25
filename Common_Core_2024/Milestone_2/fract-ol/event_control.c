/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:33:23 by igilani           #+#    #+#             */
/*   Updated: 2025/02/25 12:37:35 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_menu(t_data *fractal)
{
	char	*str[6];
	char	*iter_str;
	char	*iter_num;
	int		i;

	i = -1;
	mlx_string_put(fractal->mlx, fractal->win, 4, 12, GREY, "COMMANDS:");
	str[0] = "Esc: exit";
	str[1] = "Arrows: move";
	str[2] = "Mouse scroll: zoom";
	str[3] = "+: increase precision (iterations)";
	str[4] = "-: decrease precision (iterations)";
	str[5] = "R: reset values";
	while (++i < 6)
		mlx_string_put(fractal->mlx, fractal->win, 4, (i + 2) * 15,
			WHITE, str[i]);
	iter_num = ft_itoa(fractal->iter);
	iter_str = ft_strjoin("Iterations: ", iter_num);
	if (iter_str && iter_num)
	{
		mlx_string_put(fractal->mlx, fractal->win, 4, (i + 2) * 15,
			YELLOW, iter_str);
		free(iter_str);
		free(iter_num);
	}
}

static int	close_window(t_data *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->img);
	mlx_destroy_window(fractal->mlx, fractal->win);
	mlx_destroy_display(fractal->mlx);
	free(fractal->mlx);
	exit(EXIT_SUCCESS);
}

static int	key_hook(int keysym, t_data *fractal)
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
	else if (keysym == XK_r)
		data_init(fractal);
	fractal_render(fractal);
	return (0);
}

static int	mouse_hook(int button, int x, int y, t_data *fractal)
{
	if (button == Button4 || button == Button5)
	{
		fractal->mouse_x = map(x, -2, 2, WIDTH) * fractal->zoom
			+ fractal->offset_x;
		fractal->mouse_y = map(y, 2, -2, HEIGHT) * fractal->zoom
			+ fractal->offset_y;
		if (button == Button5)
			fractal->zoom *= 1.05;
		else
			fractal->zoom *= 0.95;
		fractal->new_mouse_x = map(x, -2, 2, WIDTH) * fractal->zoom
			+ fractal->offset_x;
		fractal->new_mouse_y = map(y, 2, -2, HEIGHT) * fractal->zoom
			+ fractal->offset_y;
		fractal->offset_x += (fractal->mouse_x - fractal->new_mouse_x);
		fractal->offset_y += (fractal->mouse_y - fractal->new_mouse_y);
		fractal_render(fractal);
	}
	return (0);
}

void	events_init(t_data *fractal)
{
	mlx_hook(fractal->win, KeyPress, KeyPressMask, key_hook, fractal);
	mlx_hook(fractal->win, ButtonPress, ButtonPressMask, mouse_hook, fractal);
	mlx_hook(fractal->win, DestroyNotify, StructureNotifyMask,
		close_window, fractal);
}
