/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:39:08 by igilani           #+#    #+#             */
/*   Updated: 2025/01/10 17:30:31 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"

int		ft_printf(const char *format, ...);
int		case_void(size_t p);
int		case_char(char *s);
int		case_unsigned(unsigned int i, const char *x);
int		case_int(int di, const char *x);

#endif