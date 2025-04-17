/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:00:02 by igilani           #+#    #+#             */
/*   Updated: 2025/04/17 20:17:24 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *dinner_routine(void *data)
{
	t_philo	*philo;
	wait_threads(philo->table);
	philo = (t_philo *)data;
	
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
	
}