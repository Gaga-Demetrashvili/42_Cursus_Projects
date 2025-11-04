/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:49:46 by gaga              #+#    #+#             */
/*   Updated: 2025/11/03 23:19:15 by gaga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime(MILISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	t_to_die = philo->data->time_to_die / 1e3;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data_f)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_f;
	while (!all_threads_running(&data->data_mutex, &data->threads_running_nbr,
			data->philo_nbr))
		;
	while (!simulation_finished(data))
	{
		i = -1;
		while (++i < data->philo_nbr && !simulation_finished(data))
		{
			if (philo_died(data->philos + i))
			{
				set_bool(&data->data_mutex, &data->end_simulation, true);
				write_status(DIED, data->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}
