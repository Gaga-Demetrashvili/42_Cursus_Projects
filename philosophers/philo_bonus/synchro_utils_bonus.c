/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:10:49 by gaga              #+#    #+#             */
/*   Updated: 2025/11/05 00:30:18 by gaga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_all_threads(t_data *data)
{
	while (!get_bool(&data->data_semaphore, &data->all_threads_ready))
		;
}

bool	all_threads_running(sem_t *semaphore, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	safe_semaphore_handle(semaphore, WAIT, 0);
	if (*threads == philo_nbr)
		ret = true;
	safe_semaphore_handle(semaphore, POST, 0);
	return (ret);
}

void	increase_long(sem_t *semaphore, long *value)
{
	safe_semaphore_handle(semaphore, WAIT, 0);
	(*value)++;
	safe_semaphore_handle(semaphore, POST, 0);
}

void	de_synchronize_philos(t_philo *philo)
{
	if (philo->data->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->data);
	}
	else
	{
		if (philo->id % 2 == 1)
			thinking(philo, true);
	}
}
