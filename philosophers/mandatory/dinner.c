/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 22:28:48 by gaga              #+#    #+#             */
/*   Updated: 2025/11/02 23:46:38 by gaga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	// set last meal time
	while (!simulation_finished(philo->data))
	{
		if (philo->full)
			break ;
		// eat func implementation. We continue from here
	}
	return (NULL);
}

void	dinner_start(t_data *data)
{
	int i;

	i = -1;
	if (0 == data->nbr_meals_philo_can_eat)
		return ;
	if (1 == data->nbr_meals_philo_can_eat)
		return ;
	else
		while (++i < data->philo_nbr)
			safe_thread_handle(&data->philos[i].thread_id, dinner_simulation,
				&data->philos[i], CREATE);
	data->start_simulation_time = gettime(MILISECOND);
	set_bool(&data->data_mutex, &data->all_threads_ready, true);
	i = -1;
	while (++i < data->philo_nbr)
		safe_thread_handle(&data->philos[i].thread_id, NULL, NULL, JOIN);
}