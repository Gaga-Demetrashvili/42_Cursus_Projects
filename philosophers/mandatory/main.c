/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:18:13 by gdemetra          #+#    #+#             */
/*   Updated: 2025/11/01 23:34:03 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

static void	*task(void *arg)
{
	t_philo	*philo;
	int		meals;

	philo = (t_philo *)arg;
	meals = 0;
	while (!check_simulation_stop(philo))
	{
		if (check_if_it_is_time_to_die(philo))
			return (NULL);
		eating(philo);
		meals++;
		if (philo->data->num_of_times_each_philo_must_eat > 0
			&& meals >= philo->data->num_of_times_each_philo_must_eat)
			break ;
		if (sleeping(philo))
			return (NULL);
		if (thinking(philo))
			return (NULL);
	}
	return (NULL);
}

static t_philo	*init_philo(int id, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->data = data;
	philo->last_meal_time = data->start_time;
	philo->meals_eaten = 0;
	philo->left_fork = &data->forks[id - 1];
	if (id == data->num_of_philos)
		philo->right_fork = &data->forks[0];
	else
		philo->right_fork = &data->forks[id];
	return (philo);
}

static void	thread_join_and_monitor_thread_creation(t_data *data, pthread_t *th)
{
	int	i;

	i = 0;
	pthread_create(&data->monitor_thread, NULL, &monitor, (void *)data);
	while (i < data->num_of_philos)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	pthread_join(data->monitor_thread, NULL);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (data->philos[i])
			free(data->philos[i]);
		i++;
	}
}

static void	thread_creation(t_data *data)
{
	int			i;
	pthread_t	*th;
	t_philo		*philo;

	data->start_time = get_timestamp();
	th = malloc(sizeof(pthread_t) * data->num_of_philos);
	if (!th)
		return ;
	data->philos = malloc(sizeof(t_philo *) * data->num_of_philos);
	if (!data->philos)
	{
		free(th);
		return ;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		philo = init_philo(i + 1, data);
		data->philos[i] = philo;
		pthread_create(&th[i], NULL, &task, (void *)philo);
		i++;
	}
	thread_join_and_monitor_thread_creation(data, th);
	free(data->philos);
	free(th);
}

int	main(int ac, char **av)
{
	int		error_num;
	t_data	*data;

	error_num = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	error_num = args_validation_and_initialization(av, data, ac - 1);
	if (error_num)
	{
		free(data);
		return (error_num);
	}
	if (init_mutexes(data))
	{
		free(data);
		return (2);
	}
	thread_creation(data);
	cleanup_mutexes(data);
	free(data);
	return (0);
}
