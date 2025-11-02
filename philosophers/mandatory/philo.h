/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 21:01:29 by gdemetra          #+#    #+#             */
/*   Updated: 2025/11/02 22:20:54 by gaga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// mutex: init, destroy, lock, unlock
// threads: create, join, detach
#include <errno.h>
#include <limits.h> // INT_MAX
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>    // printf
#include <stdlib.h>   // malloc, free
#include <sys/time.h> // gettimeofday
#include <unistd.h>   // write, usleep

// ANSI escape sequences for bold colored text:
// Use RST at the end of string to reset color
#define BLACK "\033[1;30m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define RST "\033[0m"

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}						t_opcode;

typedef pthread_mutex_t	t_mtx;

typedef struct s_data	t_data;

typedef struct s_fork
{
	int					id;
	t_mtx				fork;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_meals_philo_can_eat;
	long				start_simulation_time;
	bool				end_simulation;
	t_fork				*forks;
	t_philo				*philos;
}						t_data;

// Parsing
void					parse_input(t_data *data, char **av);

// Init
void					data_init(t_data *data);

// Utils
void					error_exit(const char *error);

// Safe funcs
void					*safe_malloc(size_t bytes);
void					safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void					safe_thread_handle(pthread_t *thread,
							void *(*foo)(void *), void *data, t_opcode opcode);
