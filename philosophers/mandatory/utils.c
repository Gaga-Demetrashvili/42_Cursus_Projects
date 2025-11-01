/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:51:40 by gdemetra          #+#    #+#             */
/*   Updated: 2025/11/01 23:31:46 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

long long	get_timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	get_time_diff(long long timestamp)
{
	return (get_timestamp() - timestamp);
}

int	check_simulation_stop(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->data->death_mutex);
	stop = philo->data->simulation_stop;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (stop);
}

int	check_if_it_is_time_to_die(t_philo *philo)
{
	long long	time_passed;

	time_passed = get_time_diff(philo->last_meal_time);
	if (time_passed > philo->data->time_to_die)
	{
		report_death(philo);
		return (1);
	}
	return (0);
}
