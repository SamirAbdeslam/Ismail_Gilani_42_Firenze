/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:22:34 by igilani           #+#    #+#             */
/*   Updated: 2025/05/03 13:23:57 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_time unit)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_handle("Error getting time");
	if (unit == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (unit == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (unit == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_handle("Invalid time unit");
	return (0);
}

void	fix_usleep(long time, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < time)
	{
		if (simulation_ended(table))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		remaining = time - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while (get_time(MICROSECOND) - start < time)
				;
		}
	}
}

bool	all_threads_running(pthread_mutex_t *mutex, long *threads,
		long philo_nbr)
{
	bool	return_value;

	return_value = false;
	mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		return_value = true;
	mutex_handle(mutex, UNLOCK);
	return (return_value);
}

void	increase_long(pthread_mutex_t *mutex, long *value)
{
	mutex_handle(mutex, LOCK);
	(*value)++;
	mutex_handle(mutex, UNLOCK);
}

void	de_sync_philo(t_philo *philo)
{
	if (philo->table->philo_number % 2 == 0)
	{
		if (philo->id % 2 == 0)
			fix_usleep(3000, philo->table);
	}
	else
	{
		if (philo->id % 2)
			think(philo, true);
	}
}
