/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:12:30 by igilani           #+#    #+#             */
/*   Updated: 2025/04/24 17:19:47 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_data(&table, argv);
		data_init(&table);
		dinner_start(&table);
		free_all(&table);
	}
	else
		error_handle("Use ./philo <number_of_philosophers> "
			"<time_to_die> <time_to_eat> <time_to_sleep> [<max_meals>]");
	return (0);
}
