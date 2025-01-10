/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:50:04 by igilani           #+#    #+#             */
/*   Updated: 2025/01/10 17:30:44 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	case_char(char *s)
{
	if (s == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	else
	{
		ft_putstr_fd(s, 1);
		return (ft_strlen(s));
	}
}
