/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_void.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:54:24 by igilani           #+#    #+#             */
/*   Updated: 2025/01/07 21:06:23 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	case_void(char *s)
{
	if(s == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		return(5);
	}
	else
	{
		ft_putstr_fd("0x", 1);
		return (ft_putnbr_base_fd((unsigned long)s, "0123456789abcdef", 1) + 2);
	}
}
