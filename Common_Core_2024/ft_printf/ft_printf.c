/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:51:34 by igilani           #+#    #+#             */
/*   Updated: 2025/01/06 13:58:51 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_printf(const char *format, ...)
{
	int				count;
	char			c;
	int				d;
	void			*p;
	unsigned int	i;

	count = 0;
	
	va_list lista;
	va_start(lista, format);

	while (*format)
	{
		if (*format == '%' && *(format + 1) == 'c')
		{
			c = (char)va_arg(lista, int);
			ft_putchar_fd(c, 1);
			count++;
			format++;
		}
		else if (*format == '%' && *(format + 1) == 's')
		{
			p = va_arg(lista, char *);
			ft_putstr_fd((char *)p, 1);
			count += ft_strlen((char *)p);
			format++;
			
		}
		else if (*format == '%' && *(format + 1) == 'p')
		{
			p = va_arg(lista, void *);
			ft_putstr_fd("0x", 1);
			count += 2;
			count += ft_putnbr_base_fd((unsigned long)p, "0123456789abcdef", 1);
			format++;
		}
		else if (*format == '%' && ((*(format + 1) == 'd') || *(format + 1) == 'i'))
		{
			d = va_arg(lista, int);
			p = ft_itoa(d);
			ft_putstr_fd((char *)p,1);
			count += ft_strlen((char *)p);
			free(p);
			format++;
		}
		else if (*format == '%' && *(format + 1) == 'u')
		{
			i = va_arg(lista, int);
			p = ft_utoa(i);
			ft_putstr_fd((char *)p,1);
			count += ft_strlen((char *)p);
			free(p);
			format++;
		}
		else if (*format == '%' && *(format + 1) == 'x')
		{
			i = va_arg(lista, unsigned int);
			count += ft_putnbr_base_fd((unsigned long)i, "0123456789abcdef", 1);
			format++;
		}
		else if (*format == '%' && *(format + 1) == 'X')
		{
			i = va_arg(lista, unsigned int);
			count += ft_putnbr_base_fd(i, "0123456789ABCDEF", 1);
			format++;
		}
		else if (*format == '%' && *(format + 1) == '%')
		{
			ft_putstr_fd("%",1);
			count++;
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

	return(count);
}

int main ()
{
	int i;
	int count;
	
	i = ft_printf("Mio: Cacato nel %s %d  volte, %c - %p - Stampato: %i - %u - %x - %X - %%", "puzzo", 42, 'A', &i, -42, -42, 2025, 2025);
	printf("\n");
	count = printf("Suo: Cacato nel %s %d  volte, %c - %p - Stampato: %i - %u - %x - %X - %%", "puzzo", 42, 'A', &i, -42, -42, 2025, 2025);
	printf("\n\nStampato da printf: %d\nStampato da ft_printf: %d", count, i);
}