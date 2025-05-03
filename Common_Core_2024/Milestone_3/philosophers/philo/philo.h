/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:05:42 by igilani           #+#    #+#             */
/*   Updated: 2025/05/03 12:58:53 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_table	t_table;

typedef enum status
{
	THINKING,
	EATING,
	SLEEPING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_status;

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

typedef enum time
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	long			meals_counter;
	bool			full;
	long			last_meal;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id; //philosopher
	pthread_mutex_t	philo_mutex;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	long			philo_number;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meals;
	long			start_simulation;
	bool			end_simulation;
	bool			threads_ready;
	long			threads_running_nbr;
	pthread_t		monitor_thread;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	print_mutex;
	t_fork			*forks;
	t_philo			*philos;
}	t_table;

/*  INIT 3*/
void	data_init(t_table *table);
void	thread_handle(pthread_t *thread, void *(*func)(void *),
			void *data, t_opcode opcode);
void	mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);

/* PARSING 3*/
long	ft_atol(const char *nptr);
int		ft_isdigit(int c);
void	parse_data(t_table *table, char **argv);

/* SET & GET 5*/
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *value);
bool	simulation_ended(t_table *table);

/* SYNC 5*/
void	wait_threads(t_table *table);
long	get_time(t_time unit);
void	fix_usleep(long time, t_table *table);
void	increase_long(pthread_mutex_t *mutex, long *value);
bool	all_threads_running(pthread_mutex_t *mutex,
			long *threads, long philo_nbr);
void	de_sync_philo(t_philo *philo);

/* MONITORING 1*/
void	*monitoring_routine(void *data);

/* DINNER 5*/
void	*dinner_routine(void *data);
void	dinner_start(t_table *table);
void	think(t_philo *philo, bool pre_sim);

/* PRINT */
void	print_status(t_status status, t_philo *philo);

/* ERROR */
int		error_syntax(char *str);
void	error_handle(char *error_message);
void	free_all(t_table *table);

#endif