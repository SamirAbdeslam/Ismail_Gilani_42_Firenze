/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:51:34 by igilani           #+#    #+#             */
/*   Updated: 2025/01/01 16:32:40 by igilani          ###   ########.fr       */
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
			p = va_arg(lista, void*);
			//count += ft_strlen(p);
			printf("Qui: %p", &p);
			//ft_putstr_fd(&p, 1);
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
	
	i = ft_printf("Cacato nel %s %d volte, %c - %p", "puzzo", 42, 'A', &i);
	printf("\n%d - %p", i, &i);
}