/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:39:08 by igilani           #+#    #+#             */
/*   Updated: 2025/01/07 19:47:26 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"

int		ft_printf(const char *format, ...);
void	ft_character(char c);
int		case_void(char *s);
int		case_s(char *s);
int		case_x(unsigned int i, const char *x);
int		case_int(int di, const char *x);

#endif