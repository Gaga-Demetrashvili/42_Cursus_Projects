/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 21:01:29 by gdemetra          #+#    #+#             */
/*   Updated: 2025/11/04 22:43:28 by gaga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <limits.h> // INT_MAX
// mutex: init, destroy, lock, unlock
// threads: create, join, detach
#include <pthread.h>
#include <semaphore.h>
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

#define DEBUG_MODE 0

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED
}						t_philo_status;

typedef enum e_opcode
{
	WAIT,
	POST,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}						t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND
}						t_time_code;

typedef pthread_mutex_t	t_mtx;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	int					forks;
	bool				has_both_forks;
	pthread_t			thread_id;
	sem_t				philo_semaphore;
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
	// synchronize philos to begin simulation simultaniously
	bool				all_threads_ready;
	long				threads_running_nbr;
	sem_t				data_semaphore;
	pthread_t			monitor;
	sem_t				write_semaphore;
	sem_t				forks;
	t_philo				*philos;
}						t_data;

// Parsing
void					parse_input(t_data *data, char **av);

// Init
void					data_init(t_data *data);

// Dinner
void					dinner_start(t_data *data);
void					thinking(t_philo *philo, bool pre_simulation);

// Utils
void					error_exit(const char *error);
long					gettime(t_time_code time_code);
void					precise_usleep(long usec, t_data *data);
void					clean(t_data *data);

// Write
void					write_status(t_philo_status status, t_philo *philo,
							bool debug);

// Monitor
void					*monitor_dinner(void *data);

// Synchro utils
void					wait_all_threads(t_data *data);
bool					all_threads_running(t_mtx *mutex, long *threads,
							long philo_nbr);
void					increase_long(t_mtx *mutex, long *value);
void					de_synchronize_philos(t_philo *philo);

// Safe funcs
void					*safe_malloc(size_t bytes);
void					safe_semaphore_handle(sem_t *semaphore, t_opcode opcode,
							unsigned int value);
void					safe_thread_handle(pthread_t *thread,
							void *(*foo)(void *), void *data, t_opcode opcode);

// Setters and Getters
void					set_bool(t_mtx *mutex, bool *dest, bool value);
bool					get_bool(t_mtx *mutex, bool *value);
void					set_long(t_mtx *mutex, long *dest, long value);
long					get_long(t_mtx *mutex, long *value);
bool					simulation_finished(t_data *data);