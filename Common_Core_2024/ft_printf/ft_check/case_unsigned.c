/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_unsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:36:19 by igilani           #+#    #+#             */
/*   Updated: 2025/01/10 17:30:37 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	case_unsigned(unsigned int i, const char *x)
{
	char	*r;
	int		n;

	if (*x == 'x')
	{
		return (ft_putnbr_base_fd((unsigned long)i, "0123456789abcdef", 1));
	}
	else if (*x == 'X')
	{
		return (ft_putnbr_base_fd((unsigned long)i, "0123456789ABCDEF", 1));
	}
	else if (*x == 'u')
	{
		r = ft_utoa(i);
		ft_putstr_fd(r, 1);
		n = ft_strlen(r);
		free(r);
		return (n);
	}
	return (0);
}
