/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:27:30 by igilani           #+#    #+#             */
/*   Updated: 2025/01/05 19:57:15 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base_fd(unsigned long n, char *base, int fd)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += ft_putnbr_base_fd (n / 16, base, fd);
	count += write (fd, &base[n % 16], 1);
	return (count);
}
