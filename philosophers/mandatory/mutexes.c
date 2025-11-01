/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:53:24 by gdemetra          #+#    #+#             */
/*   Updated: 2025/11/01 21:47:08 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_forks_mutexes(t_data *data, int i)
{
	while (i--)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
}

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			cleanup_forks_mutexes(data, i);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0
		|| pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		cleanup_forks_mutexes(data, data->num_of_philos);
		return (1);
	}
	return (0);
}

void	cleanup_mutexes(t_data *data)
{
	cleanup_forks_mutexes(data, data->num_of_philos);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_mutex);
}
