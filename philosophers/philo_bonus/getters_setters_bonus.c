/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 23:19:03 by gaga              #+#    #+#             */
/*   Updated: 2025/11/05 00:25:27 by gaga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_bool(sem_t *semaphore, bool *dest, bool value)
{
	safe_semaphore_handle(semaphore, WAIT, 0);
	*dest = value;
	safe_semaphore_handle(semaphore, POST, 0);
}

bool	get_bool(sem_t *semaphore, bool *value)
{
	bool	ret;

	safe_semaphore_handle(semaphore, WAIT, 0);
	ret = *value;
	safe_semaphore_handle(semaphore, POST, 0);
	return (ret);
}

void	set_long(sem_t *semaphore, long *dest, long value)
{
	safe_semaphore_handle(semaphore, WAIT, 0);
	*dest = value;
	safe_semaphore_handle(semaphore, POST, 0);
}

long	get_long(sem_t *semaphore, long *value)
{
	long	ret;

	safe_semaphore_handle(semaphore, WAIT, 0);
	ret = *value;
	safe_semaphore_handle(semaphore, POST, 0);
	return (ret);
}

bool	simulation_finished(t_data *data)
{
	return (get_bool(&data->data_semaphore, &data->end_simulation));
}
