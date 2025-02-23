/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:13:15 by igilani           #+#    #+#             */
/*   Updated: 2025/02/23 11:36:04 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 800
# define HEIGHT 800
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define ELETRIC_BLUE 0x0066FF

# include "tha_supreme_lib/tha_supreme_lib.h"
# include "minilibx-linux/mlx_int.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <X11/keysym.h>

typedef struct	s_complex {
	double	r;
	double	i;
}		t_complex;

typedef struct	s_keys {
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	up;
	int	down;
}		t_keys;

typedef struct	s_data {
	void	*mlx;       // Connessione principale a MinilibX
	void	*win;       // Finestra grafica
	char	*title;     // Titolo finestra
	void	*img;       // Immagine buffer per il rendering
	char	*addr;      // Indirizzo dati immagine
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	hypotenuse; // Teorema di pitagora per controllare se e' in Mandelbrot
	
	// Parametri del frattale
	double	offset_x;   // Spostamento sull'asse X
	double	offset_y;   // Spostamento sull'asse Y
	double	zoom;       // Livello di zoom
	int		iter;   // Massime iterazioni per precisione
	
	// Gestione colori
	int		color;
	
	// Input utente
	t_keys	keys;
	int		is_julia;   // Flag per Julia set
	double	julia_r;
    double	julia_i;
	double	mouse_x;    // Posizione X mouse
	double	mouse_y;    // Posizione Y mouse
}		t_data;

void	fractal_render(t_data *fractal);

double	map(double unscaled_num, double new_min, double new_max, double old_max);
t_complex	sum_compl(t_complex z1, t_complex z2);
t_complex	square_compl(t_complex z);
#endif