/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:31:12 by igilani           #+#    #+#             */
/*   Updated: 2025/04/07 18:31:32 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_table(t_table *table)
{
	printf("Philosopher number: %ld\n", table->philo_number);
	printf("Time to die: %ld\n", table->time_to_die);
	printf("Time to eat: %ld\n", table->time_to_eat);
	printf("Time to sleep: %ld\n", table->time_to_sleep);
	if (table->max_meals != -1)
		printf("Max meals: %ld\n", table->max_meals);
	else
		printf("Max meals: No limit\n");
}