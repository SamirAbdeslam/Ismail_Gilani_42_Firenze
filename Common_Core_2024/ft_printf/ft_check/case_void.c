/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_void.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:54:24 by igilani           #+#    #+#             */
/*   Updated: 2025/01/06 19:15:52 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int	case_void(char *s)
{
	ft_putstr_fd("0x", 1);
	return (ft_putnbr_base_fd((unsigned long)s, "0123456789abcdef", 1) + 2);
}
