/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 21:01:29 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/30 22:34:11 by gdemetra         ###   ########.fr       */
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
	int				args[5];
	pthread_mutex_t	*forks;
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

int					args_validation_and_initialization(int ac, char **argv,
						int *args, int num_of_args);

int					init_mutexes(t_data *data);
void				cleanup_mutexes(t_data *data);

long long			get_timestamp(void);
long long			get_time_diff(long long timestamp);
