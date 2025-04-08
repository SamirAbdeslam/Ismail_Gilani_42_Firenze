/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:11:14 by igilani           #+#    #+#             */
/*   Updated: 2025/04/08 18:49:03 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void parse_data(char **argv)
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
}

void mutex_init(t_fork *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		pthread_mutex_lock(&mutex->mutex);
	else if (UNLOCK == opcode)
		pthread_mutex_unlock(&mutex->mutex);
	else if (INIT == opcode)
		pthread_mutex_init(&mutex->mutex, NULL);
	else if (DESTROY == opcode)
		pthread_mutex_destroy(&mutex->mutex);
	else
		error_handle("Invalid mutex operation");
}

void data_init(t_table *table, char **argv)
{
	table->philo_number = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (table->time_to_die < 60000 || table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		error_handle("Time values must be greater than 60 seconds");
	if (argv[5])
		table->max_meals = ft_atol(argv[5]);
	else
		table->max_meals = -1; // No limit on meals
	table->end_simulation = false;
	table->philos = malloc(sizeof(t_philo) * table->philo_number);
	if (!table->philos)
		error_handle("Memory allocation failed");
}
