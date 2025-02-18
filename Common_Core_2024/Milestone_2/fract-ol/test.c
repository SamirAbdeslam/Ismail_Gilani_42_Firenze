// int main(int argc, char **argv)
// {
// 	//usage(argc, argv);
// 	// t_data	data;
// 	// int		y;
// 	// int		x;
// 	// int		offset;
// 	int		i = 0;
// 	(void)argc;
	
// 	t_complex z;
// 	t_complex c; //punto specifico del frattale
// 	double temp;

// 	z.r = 0;
// 	z.i = 0;

// 	c.r = atof(argv[1]);
// 	c.i = atof(argv[2]);

// 	while(i < ft_atoi(argv[3]))
// 	{
// 		temp = (z.r * z.r) - (z.i * z.i);
		
// 		z.i = 2 * z.r * z.i;
// 		z.r = temp;

// 		z.r += c.r;
// 		z.i += c.i;

// 		printf("Iterazione ->%d: Reale = %f, Immaginario = %f\n", i, z.r, z.i);
// 		i++;
// 	}
// 	return (0);
// }
	// mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	// mlx_key_hook(data->win, key_hook, &data);
	// mlx_hook(data->win, 17, 0, close_window, NULL);
	// mlx_loop(data->mlx);

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