/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:00:02 by igilani           #+#    #+#             */
/*   Updated: 2025/04/18 18:09:47 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *dinner_routine(void *data)
{
	t_philo	*philo;
	philo = (t_philo *)data;
	wait_threads(philo->table);
	
	while (!simulation_ended(philo->table))
	{
		if (philo->full)
			break;
		eat(philo);
		
	}
	return (NULL);
}

void dinner_start(t_table *table)
{
	int i;
	
	i = -1;
	if (table->max_meals == 0)
		return;
	else if (table->philo_number == 1)
		one_philo(); //TODO
	else
	{
		while (++i < table->philo_number)
			thread_handle(&table->philos[i].thread_id, dinner_routine, &table->philos[i], CREATE);
	}
	table->start_simulation = get_time(MILLISECOND);
	set_bool(&table->table_mutex, &table->threads_ready, true);

	i = -1;
	while (++i < table->philo_number)
		thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
}
