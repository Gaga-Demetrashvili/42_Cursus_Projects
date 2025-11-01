/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:00:00 by gdemetra          #+#    #+#             */
/*   Updated: 2025/11/01 23:35:39 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	*monitor(void *arg)
{
	int			i;
	t_data		*data;
	long long	time_passed;

	data = (t_data *)arg;
	while (!data->simulation_stop)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			if (data->philos[i])
			{
				time_passed = get_time_diff(data->philos[i]->last_meal_time);
				if (time_passed > data->time_to_die)
				{
					report_death(data->philos[i]);
					return (NULL);
				}
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
