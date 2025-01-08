/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:51:34 by igilani           #+#    #+#             */
/*   Updated: 2025/01/08 01:42:27 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check(const char *format, va_list lista)
{
	int	count;

	count = 0;
	if (va_arg(lista, void *) == NULL)
	{
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
	}
	else
		return(-1);
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
			if(ft_check((format + 1), lista) == -1)
				return(0);
			else
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
int main ()
{
	int i;
	int count;
	
	i = ft_printf("Mio: Cacato nel %s %d  volte, %c - %p - Stampato: %i - %u - %x - %X - %%", "puzzo", 42, 'A', &i, -42, -42, 2025, 2025);
	printf("\n");
	count = printf("Suo: Cacato nel %s %d  volte, %c - %p - Stampato: %i - %u - %x - %X - %%", "puzzo", 42, 'A', &i, -42, -42, 2025, 2025);
	printf("\n\nStampato da printf: %d\nStampato da ft_printf: %d", count, i);

	ft_printf("NULL %s", NULL);
}