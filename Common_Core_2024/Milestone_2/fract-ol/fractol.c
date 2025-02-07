/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:15:58 by igilani           #+#    #+#             */
/*   Updated: 2025/02/07 19:09:27 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int key_press(int keycode, void *param) {
    (void)param;
    if (keycode == XK_Escape)
        exit(0);
    return (0);
}

int close_window(void *param) {
    (void)param;
    exit(0);
}

int main()
{
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, WIDTH, HEIGHT, "Fractol");
	void	*img = mlx_new_image(mlx, WIDTH, HEIGHT);
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	char	*buffer = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
	
	int	y;
	int	x;
	int	offset;
	x = 100;
	y = 100;
	offset = (y * line_length) + (x * 4);

	buffer[offset] = 0x00;
	buffer[offset + 1] = 0x00;
	buffer[offset + 2] = 0xFF;

	mlx_put_image_to_window(mlx, win, img, 0, 0);

    mlx_key_hook(win, key_press, NULL);
    mlx_hook(win, 17, 0, close_window, NULL);
	mlx_loop(mlx);
	return(0);
}