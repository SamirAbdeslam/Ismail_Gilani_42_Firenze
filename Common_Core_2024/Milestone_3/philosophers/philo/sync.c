/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:22:34 by igilani           #+#    #+#             */
/*   Updated: 2025/04/20 12:04:07 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time(t_time unit)
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
	return (1337);
}

void fix_usleep(long time, t_table *table)
{
	long start;
	long elapsed;
	long remaining;

	start = get_time(MICROSECOND);

	while (get_time(MICROSECOND) - start < time)
	{
		if (simulation_ended(table))
			break;
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

void wait_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->threads_ready))
		;
}