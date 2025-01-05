/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:51:34 by igilani           #+#    #+#             */
/*   Updated: 2025/01/05 19:49:33 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int ft_printf(const char *format, ...)
{
	int	count;
	char	c;
	char	*s;
	int	d;
	void	*p;
	unsigned int	i;
	char	*u;
	void	*x;
	void	*X;
	
	count = 0;
	
	va_list lista;
	va_start(lista, format);

	while(*format)
	{
		if(*format == '%' && *(format + 1) == 'c')
		{
			c = (char)va_arg(lista, int);
			ft_putchar_fd(c,1);
			count++;
			format++;
		}
		else if(*format == '%' && *(format + 1) == 's')
		{
			s = va_arg(lista, char*);
			count += ft_strlen(s);
			ft_putstr_fd(s,1);
			format++;
			
		}
		else if(*format == '%' && *(format + 1) == 'p')
		{
			p = va_arg(lista, void *);
			ft_putstr_fd("0x", 1);
			count += 2;
			count += ft_putnbr_base_fd((unsigned long)p, "0123456789abcdef", 1);
			format++;
		}
		else if(*format == '%' && *(format + 1) == 'd')
		{
			d = va_arg(lista, int);
			s = ft_itoa(d);
			ft_putstr_fd(s,1);
			count += ft_strlen(s);
			free(s);
			format++;
		}
		else if(*format == '%' && *(format + 1) == 'i')
		{
			i = va_arg(lista, int);
			s = ft_itoa(i);
			ft_putstr_fd(s,1);
			count += ft_strlen(s);
			free(s);
			format++;
		}
		else if(*format == '%' && *(format + 1) == 'u')
		{
			i = va_arg(lista, int);
			u = ft_utoa(i);
			ft_putstr_fd(u,1);
			count += ft_strlen(u);
			format++;
		}
		else if(*format == '%' && *(format + 1) == 'x')
		{
			x = va_arg(lista, void *);
			count += ft_putnbr_base_fd((unsigned long)x, "0123456789abcdef", 1);
			format++;
		}
		else if(*format == '%' && *(format + 1) == 'X')
		{
			X = va_arg(lista, void *);
			count += ft_putnbr_base_fd((unsigned long)X, "0123456789ABCDEF", 1);
			format++;
		}
		else if(*format == '%' && *(format + 1) == '%')
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
	
	i = ft_printf("Cacato nel %s %d  volte, %c - %p - Stampato: %i - %u - %x - %X - %%", "puzzo", 42, 'A', &i, 42, -42, 2025, 2025);
	printf("\nCacato nel %s %d  volte, %c - %p - Stampato: %i - %u - %x- %X - %%", "puzzo", 42, 'A', &i, i, -42, 2025, 2025);
}