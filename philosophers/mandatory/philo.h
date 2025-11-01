/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 21:01:29 by gdemetra          #+#    #+#             */
/*   Updated: 2025/11/01 23:34:17 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum e_args
{
	NUM_OF_PHILOS,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUM_OF_TIMES_EACH_PHILO_MUST_EAT
}					t_args;

typedef struct s_data
{
	int				num_of_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				num_of_times_each_philo_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	struct s_philo	**philos;
	pthread_t		monitor_thread;
	int				simulation_stop;
	long long		start_time;
}					t_data;

typedef struct s_philo
{
	int				id;
	struct s_data	*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_meal_time;
	int				meals_eaten;
}					t_philo;

// Validation
int					args_validation_and_initialization(char **argv,
						t_data *data, int num_of_args);

// Mutexes
int					init_mutexes(t_data *data);
void				cleanup_mutexes(t_data *data);

// Utils
long long			get_timestamp(void);
long long			get_time_diff(long long timestamp);
int					check_simulation_stop(t_philo *philo);
int					check_if_it_is_time_to_die(t_philo *philo);

// Actions
void				eating(t_philo *philo);
int					sleeping(t_philo *philo);
int					thinking(t_philo *philo);

// Actions utils
int					taking_fork_for_even_numbered_philo(t_philo *philo);
int					taking_fork_for_odd_numbered_philo(t_philo *philo);
void				print_action(t_philo *philo, const char *action);
void				report_death(t_philo *philo);

// Monitor
void				*monitor(void *arg);