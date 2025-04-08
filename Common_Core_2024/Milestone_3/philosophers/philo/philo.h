/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:05:42 by igilani           #+#    #+#             */
/*   Updated: 2025/04/08 18:42:05 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/time.h>
#include <pthread.h>

typedef enum opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef struct s_fork
{
	pthread_mutex_t mutex;
	int		id;
}	t_fork;

typedef struct s_philo
{
	int		id;
	long	meals_counter;
	bool 	full;
	long	last_meal;
	t_fork	*first_fork;
	t_fork	*last_fork;
	pthread_t thread_id; //philosopher
}	t_philo;

typedef struct s_table
{
	long	philo_number;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	max_meals;
	long	start_simulation;
	bool	end_simulation;
	t_fork	*forks;
	t_philo	*philos;
}	t_table;


/*  INIT */
void parse_data(char **argv);
void data_init(t_table *table, char **argv);

/* UTILS */
long	ft_atol(const char *nptr);
int	ft_isdigit(int c);

/* ERROR */
int	error_syntax(char *str);
void	error_handle(char *error_message);


/* DEBUG */
void print_table(t_table *table);
#endif