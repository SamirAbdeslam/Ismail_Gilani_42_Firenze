/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:04:47 by igilani           #+#    #+#             */
/*   Updated: 2025/04/24 17:22:09 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_number)
	{
		philo = table->philos + i;
		mutex_handle(&philo->philo_mutex, DESTROY);
	}
	mutex_handle(&table->print_mutex, DESTROY);
	mutex_handle(&table->table_mutex, DESTROY);
	free(table->philos);
	free(table->forks);
}

void	error_handle(char *error_message)
{
	printf("Error: %s\n", error_message);
	exit(EXIT_FAILURE);
}

int	error_syntax(char *str)
{
	if (!(*str == '+' || *str == '-' || ft_isdigit(*str)))
		return (1);
	if (*str == '-')
		return (1);
	while (*++str)
	{
		if (!ft_isdigit(*str))
			return (1);
	}
	return (0);
}
