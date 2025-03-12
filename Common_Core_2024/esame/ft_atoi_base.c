/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:41:23 by igilani           #+#    #+#             */
/*   Updated: 2025/03/12 19:35:26 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	ft_atoi_base(const char *str, int str_base)
{
	int i = 0;
	int sign = 1;
	
	if (!str || str_base < 2 || str_base > 16)
		return(0);
	while (str[i] >= 9 && (str[i] <= 13 || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	int nbr = 0;
	while(str[i])
	{
		// nbr *= str_base;

		if (str[i] >= '0' && str[i] <= '9')
			nbr = nbr * str_base + str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F')
			nbr = nbr * str_base + str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			nbr = nbr * str_base + str[i] - 'a' + 10;
		else
			return(nbr * sign);
		i++;
	}
	return(nbr * sign);
}

int main()
{
	printf("%d\n", ft_atoi_base("Ceci permet de decouvrir le fonctionnement de ton ft_atoi_base.", 16));
	printf("Test base 10: %d\n", ft_atoi_base("    123   ", 10));  // 123
    printf("Test base 10 (negativo): %d\n", ft_atoi_base("-123", 10));  // -123
    printf("Test base 16: %d\n", ft_atoi_base("A3", 16));  // 163
    printf("Test base 16 (minuscole): %d\n", ft_atoi_base("a3", 16));  // 163
    printf("Test base 2: %d\n", ft_atoi_base("1011", 2));  // 11
    printf("Test base 8: %d\n", ft_atoi_base("77", 8));  // 63
    printf("Test base 16 con segno: %d\n", ft_atoi_base("-1F", 16));  // -31
    printf("Test base 5: %d\n", ft_atoi_base("321", 5));  // 3*5^2 + 2*5^1 + 1 = 86
    printf("Test con spazi: %d\n", ft_atoi_base("   42", 10));  // 42
    printf("Test con caratteri non validi: %d\n", ft_atoi_base("123G", 16));  // 123 (ferma alla G)
    printf("Test base non valida: %d\n", ft_atoi_base("123", 20));  // 0 (base fuori range)
}