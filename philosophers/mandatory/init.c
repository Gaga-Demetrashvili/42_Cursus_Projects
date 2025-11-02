/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:54:31 by gaga              #+#    #+#             */
/*   Updated: 2025/11/02 22:20:09 by gaga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 0 left_fork | id 1 philo | 1 right_fork

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->data->philo_nbr;
	philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

static void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->philo_nbr)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->data = data;
		assign_forks(philo, data->forks, i);
	}
}

void	data_init(t_data *data)
{
	int i;

	i = -1;
	data->end_simulation = false;
	data->philos = safe_malloc(sizeof(t_philo) * data->philo_nbr);
	data->forks = safe_malloc(sizeof(t_fork) * data->philo_nbr);
	while (++i < data->philo_nbr)
	{
		safe_mutex_handle(&data->forks[i], INIT);
		data->forks[i].id = i;
	}
	philo_init(data);
}