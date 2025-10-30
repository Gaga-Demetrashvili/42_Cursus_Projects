/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:18:13 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/30 23:25:47 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <unistd.h>

void	*task(void *arg)
{
	t_philo		*philo;
	long long	start_time;

	philo = (t_philo *)arg;
	start_time = get_timestamp();
	pthread_mutex_lock(philo->left_fork);
	printf("%lld %d has taken a fork\n", get_timestamp(), philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("%lld %d has taken a fork\n", get_timestamp(), philo->id);
	printf("%lld %d is eating\n", get_timestamp(), philo->id);
	usleep(philo->data->args[TIME_TO_EAT] * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}

t_philo	*init_philo(int id, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->id = id;
	philo->data = data;
	philo->last_meal_time = 0;
	philo->meals_eaten = 0;
	philo->left_fork = &data->forks[id - 1];
	if (id == data->args[NUM_OF_PHILOS])
		philo->right_fork = &data->forks[0];
	else
		philo->right_fork = &data->forks[id];
	return (philo);
}

void	thread_creation(t_data *data)
{
	int			i;
	pthread_t	th[data->args[NUM_OF_PHILOS]];
	t_philo		*philo;

	i = 0;
	while (i < data->args[NUM_OF_PHILOS])
	{
		philo = init_philo(i + 1, data);
		pthread_create(&th[i], NULL, &task, (void *)philo);
		i++;
	}
	i = 0;
	while (i < data->args[NUM_OF_PHILOS])
	{
		pthread_join(th[i], NULL);
		i++;
	}
}

void	set_data_args(t_data *data, int *args)
{
	data->args[NUM_OF_PHILOS] = args[NUM_OF_PHILOS];
	data->args[TIME_TO_DIE] = args[TIME_TO_DIE];
	data->args[TIME_TO_EAT] = args[TIME_TO_EAT];
	data->args[TIME_TO_SLEEP] = args[TIME_TO_SLEEP];
	data->args[NUM_OF_TIMES_EACH_PHILO_MUST_EAT] = args[NUM_OF_TIMES_EACH_PHILO_MUST_EAT];
}

void	test_data_args_init(int *args)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		printf("%d\n", args[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	int		args[5];
	int		error_num;
	t_data	*data;

	memset(args, 0, sizeof(args));
	error_num = 0;
	error_num = args_validation_and_initialization(ac, av, args, ac - 1);
	if (error_num)
		return (error_num);
	data = malloc(sizeof(t_data));
	set_data_args(data, args);
	init_mutexes(data);
	thread_creation(data);
	cleanup_mutexes(data);
	return (0);
}
