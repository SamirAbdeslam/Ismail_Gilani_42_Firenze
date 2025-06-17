/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:50:22 by igilani           #+#    #+#             */
/*   Updated: 2025/06/17 18:03:35 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed_time;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed_time = get_time(MILLISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal);
	time_to_die = philo->table->time_to_die / 1000;
	if (elapsed_time > time_to_die)
		return (true);
	return (false);
}

void	*monitoring_routine(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	// while (!all_threads_running(&table->table_mutex,
	// 		&table->threads_running_nbr, table->philo_number))
	// 	;
	while (!simulation_ended(table))
	{
		i = -1;
		while (++i < table->philo_number && !simulation_ended(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				print_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}
