/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:00:02 by igilani           #+#    #+#             */
/*   Updated: 2025/04/20 12:01:52 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void think(t_philo *philo) //TODO
{
	print_status(THINKING, philo);
}

static void eat(t_philo *philo)
{
	mutex_handle(&philo->first_fork->fork, LOCK);
	print_status(TAKE_FIRST_FORK, philo);
	mutex_handle(&philo->second_fork->fork, LOCK);
	print_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal, get_time(MILLISECOND));
	philo->meals_counter++;
	print_status(EATING, philo);
	fix_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->max_meals > 0 && philo->meals_counter == philo->table->max_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	mutex_handle(&philo->first_fork->fork, UNLOCK);
	mutex_handle(&philo->second_fork->fork, UNLOCK);
}

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
		print_status(SLEEPING, philo);
		fix_usleep(philo->table->time_to_sleep, philo->table);
		think(philo);
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
		print_status(DIED, &table->philos[0]);
		//one_philo(); //TODO
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
