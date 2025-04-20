/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:11:14 by igilani           #+#    #+#             */
/*   Updated: 2025/04/20 11:59:25 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void thread_handle(pthread_t *thread, void *(*func)(void *), void *data, t_opcode opcode)
{
	if (CREATE == opcode)
	{
		if (pthread_create(thread, NULL, func, data) != 0)
			error_handle("Thread creation failed");
	}
	else if (JOIN == opcode)
	{
		if (pthread_join(*thread, NULL) != 0)
			error_handle("Thread join failed");
	}
	else if (DETACH == opcode)
	{
		if (pthread_detach(*thread) != 0)
			error_handle("Thread detach failed");
	}
	else
	{
		error_handle("Invalid thread operation");
	}
}

void mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
	{
		if (pthread_mutex_lock(mutex) != 0)
			error_handle("Mutex lock failed");
	}
	else if (UNLOCK == opcode)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			error_handle("Mutex unlock failed");
	}
	else if (INIT == opcode)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			error_handle("Mutex initialization failed");
	}
	else if (DESTROY == opcode)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			error_handle("Mutex destruction failed");
	}
	else
	{
		error_handle("Invalid mutex operation");
	}
}

static void assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int philo_nbr;

	philo_nbr = philo->table->philo_number;

	philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

static void philo_init(t_table *table)
{
	int i;
	t_philo *philo;

	i = -1;
	while (++i < table->philo_number)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		mutex_handle(&philo->philo_mutex, INIT);
		
		assign_forks(philo, table->forks, i);
	}
}

void data_init(t_table *table)
{
	int i;

	i = -1;
	table->end_simulation = false;
	table->threads_ready = false;
	table->philos = malloc(sizeof(t_philo) * table->philo_number);
	if (!table->philos)
		error_handle("Memory allocation failed for philosophers");
	mutex_handle(&table->table_mutex, INIT);
	mutex_handle(&table->print_mutex, INIT);
	table->forks = malloc(sizeof(t_fork) * table->philo_number);
	if (!table->forks)
		error_handle("Memory allocation failed for forks");
	while (++i < table->philo_number)
	{
		mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
