/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:54:31 by gaga              #+#    #+#             */
/*   Updated: 2025/11/04 23:54:15 by gaga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		safe_semaphore_handle(&philo->philo_semaphore, INIT, 1);
		philo->forks = 0;
	}
}

void	data_init(t_data *data)
{
	int	i;

	i = -1;
	data->end_simulation = false;
	data->all_threads_ready = false;
	data->threads_running_nbr = 0;
	data->philos = safe_malloc(sizeof(t_philo) * data->philo_nbr);
	safe_semaphore_handle(&data->data_semaphore, INIT, 1);
	safe_semaphore_handle(&data->write_semaphore, INIT, 1);
	safe_semaphore_handle(&data->forks, INIT, 5);
	philo_init(data);
}
