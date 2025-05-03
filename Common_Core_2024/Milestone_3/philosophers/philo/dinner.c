/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:00:02 by igilani           #+#    #+#             */
/*   Updated: 2025/05/03 13:27:13 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo, bool pre_sim)
{
	long	time_to_think;
	long	time_to_eat;
	long	time_to_sleep;

	if (!pre_sim)
		print_status(THINKING, philo);
	if (philo->table->philo_number % 2 == 0)
		return ;
	time_to_eat = philo->table->time_to_eat;
	time_to_sleep = philo->table->time_to_sleep;
	time_to_think = time_to_eat * 2 - time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	fix_usleep(time_to_think * 0.42, philo->table);
}

void	*one_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	set_long(&philo->philo_mutex, &philo->last_meal, get_time(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	print_status(TAKE_FIRST_FORK, philo);
	while (!simulation_ended(philo->table))
		usleep(200);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	mutex_handle(&philo->first_fork->fork, LOCK);
	print_status(TAKE_FIRST_FORK, philo);
	mutex_handle(&philo->second_fork->fork, LOCK);
	print_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal, get_time(MILLISECOND));
	philo->meals_counter++;
	print_status(EATING, philo);
	fix_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->max_meals > 0
		&& philo->meals_counter == philo->table->max_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	mutex_handle(&philo->first_fork->fork, UNLOCK);
	mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	*dinner_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_long(&philo->philo_mutex, &philo->last_meal, get_time(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	de_sync_philo(philo);
	while (!simulation_ended(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		print_status(SLEEPING, philo);
		fix_usleep(philo->table->time_to_sleep, philo->table);
		think(philo, false);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	table->start_simulation = get_time(MILLISECOND);
	if (table->max_meals == 0)
		return ;
	else if (table->philo_number == 1)
	{
		thread_handle(&table->philos[0].thread_id,
			one_philo, &table->philos[0], CREATE);
	}
	else
	{
		while (++i < table->philo_number)
			thread_handle(&table->philos[i].thread_id,
				dinner_routine, &table->philos[i], CREATE);
	}
	usleep(100);
	thread_handle(&table->monitor_thread, monitoring_routine, table, CREATE);
	set_bool(&table->table_mutex, &table->threads_ready, true);
	i = -1;
	while (++i < table->philo_number)
		thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	thread_handle(&table->monitor_thread, NULL, NULL, JOIN);
}
