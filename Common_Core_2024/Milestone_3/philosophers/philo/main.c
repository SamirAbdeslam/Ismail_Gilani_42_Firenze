/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:12:30 by igilani           #+#    #+#             */
/*   Updated: 2025/04/17 18:36:54 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_table	table;
	if (argc == 5 || argc == 6)
	{
		parse_data(&table, argv);
		
		data_init(&table); // Initialize the data structure
		// print_table(&table);
		
		//dinner_start(&table); // Start the dinner simulation

		//free_all(&table); // Free all allocated memory
	}
	else
		error_handle("Use ./philo <number_of_philosophers> "
			"<time_to_die> <time_to_eat> <time_to_sleep> [<max_meals>]");
	return (0);
}
