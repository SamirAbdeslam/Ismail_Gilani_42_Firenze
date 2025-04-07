/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:27:26 by igilani           #+#    #+#             */
/*   Updated: 2025/04/07 18:28:18 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void parse_data(t_table *table, char **argv)
{
	int i;
	long nbr;

	i = 1;
	nbr = 0;
	while (argv[i])
	{
		if (error_syntax(argv[i]))
			error_handle("Syntax error");
		nbr = ft_atol(argv[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
			error_handle("Integer overflow");
		++i;
	}
	table->philo_number = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->max_meals = ft_atol(argv[5]);
	else
		table->max_meals = -1; // No limit on meals
	table->end_simulation = false;
}