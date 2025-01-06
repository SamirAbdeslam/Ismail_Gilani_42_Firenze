/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:51:34 by igilani           #+#    #+#             */
/*   Updated: 2025/01/06 19:28:57 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_check(const char *format, va_list lista)
{
	int	count;

	count = 0;
	if (*format == 's')
		count += case_s(va_arg(lista, char *));
	else if (*format == 'p')
		count += case_void(va_arg(lista, void *));
	else if (*format == 'c' || *format == 'd' || *format == 'i')
		count += case_int(va_arg(lista, int), format);
	else if (*format == 'x' || *format == 'X' || *format == 'u')
		count += case_x(va_arg(lista, unsigned int), format);
	else if (*format == '%')
	{
		ft_putstr_fd("%", 1);
		count++;
		format++;
	}
	else
		return (0);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list			lista;
	int				count;

	count = 0;
	va_start(lista, format);
	while (*format)
	{
		if (*format == '%')
		{
			count += ft_check((format + 1), lista);
			format++;
		}
		else
		{
			ft_putchar_fd(*format, 1);
			count++;
		}
		format++;
	}
	va_end(lista);
	return (count);
}
