/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:29:58 by igilani           #+#    #+#             */
/*   Updated: 2025/01/10 17:29:08 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	case_int(int di, const char *x)
{
	char	*r;
	int		n;

	if (*x == 'i' || *x == 'd')
	{
		r = ft_itoa(di);
		ft_putstr_fd(r, 1);
		n = ft_strlen(r);
		free(r);
		return (n);
	}
	else if (*x == 'c')
	{
		ft_putchar_fd((char)di, 1);
		return (1);
	}
	else
		return (0);
}
