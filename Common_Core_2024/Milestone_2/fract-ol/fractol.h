/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:13:15 by igilani           #+#    #+#             */
/*   Updated: 2025/02/10 17:00:03 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 800
# define HEIGHT 600
# define KEY_ESC XK_Escape
# define KEY_PLUS XK_plus
# define KEY_MINUS XK_minus
# define KEY_SCROLL_UP 4
# define KEY_SCROLL_DOWN 5
# define KEY_UP XK_Up
# define KEY_DOWN XK_Down
# define KEY_LEFT XK_Left
# define KEY_RIGHT XK_Right
# include "tha_supreme_lib/tha_supreme_lib.h"
# include "minilibx-linux/mlx_int.h"
# include "minilibx-linux/mlx.h"
# include <math.h>

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
	void	*img;       // Immagine buffer per il rendering
	char	*addr;      // Indirizzo dati immagine
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	
	// Parametri del frattale
	double	offset_x;   // Spostamento sull'asse X
	double	offset_y;   // Spostamento sull'asse Y
	double	zoom;       // Livello di zoom
	int		max_iter;   // Massime iterazioni per precisione
	
	// Gestione colori
	int		color_pattern;
	int		color1;
	int		color2;
	
	// Input utente
	t_keys	keys;
	int		is_julia;   // Flag per Julia set
	double	mouse_x;    // Posizione X mouse
	double	mouse_y;    // Posizione Y mouse
}		t_data;

#endif