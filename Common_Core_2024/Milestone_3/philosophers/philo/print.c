/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:27:40 by igilani           #+#    #+#             */
/*   Updated: 2025/04/20 12:16:37 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_status(t_status status, t_philo *philo)
{
	long elapsed_time;

	elapsed_time = get_time(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	mutex_handle(&philo->table->print_mutex, LOCK);
	if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status) && !simulation_ended(philo->table))
		printf("%-6ld %d has taken a fork\n", elapsed_time, philo->id);
	else if (EATING == status && !simulation_ended(philo->table))
		printf("%-6ld %d is eating\n", elapsed_time, philo->id);
	else if (SLEEPING == status && !simulation_ended(philo->table))
		printf("%-6ld %d is sleeping\n", elapsed_time, philo->id);
	else if (THINKING == status && !simulation_ended(philo->table))
		printf("%-6ld %d is thinking\n", elapsed_time, philo->id);
	else if (DIED == status)
		printf("%-6ld %d died\n", elapsed_time, philo->id);
	mutex_handle(&philo->table->print_mutex, UNLOCK);
}