/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_void.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:54:24 by igilani           #+#    #+#             */
/*   Updated: 2025/01/10 17:29:27 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	case_void(size_t p)
{
	if (p == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	else
	{
		ft_putstr_fd("0x", 1);
		return (ft_putnbr_base_fd((unsigned long)p, "0123456789abcdef", 1) + 2);
	}
	return (0);
}
