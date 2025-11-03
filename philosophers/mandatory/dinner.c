/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 22:28:48 by gaga              #+#    #+#             */
/*   Updated: 2025/11/03 22:16:56 by gaga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

static void	eating(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->nbr_meals_philo_can_eat > 0
		&& philo->meals_counter == philo->data->nbr_meals_philo_can_eat)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

static void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	increase_long(&philo->data->data_mutex, &philo->data->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finished(philo->data))
		usleep(200);
	return (NULL);
}

static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	increase_long(&philo->data->data_mutex, &philo->data->threads_running_nbr);
	while (!simulation_finished(philo->data))
	{
		if (philo->full)
			break ;
		eating(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->data->time_to_sleep, philo->data);
		thinking(philo);
	}
	return (NULL);
}

void	dinner_start(t_data *data)
{
	int	i;

	i = -1;
	if (0 == data->nbr_meals_philo_can_eat)
		return ;
	else if (1 == data->philo_nbr)
		safe_thread_handle(&data->philos[0].thread_id, lone_philo,
			&data->philos[0], CREATE);
	else
		while (++i < data->philo_nbr)
			safe_thread_handle(&data->philos[i].thread_id, dinner_simulation,
				&data->philos[i], CREATE);
	safe_thread_handle(&data->monitor, monitor_dinner, data, CREATE);
	data->start_simulation_time = gettime(MILISECOND);
	set_bool(&data->data_mutex, &data->all_threads_ready, true);
	i = -1;
	while (++i < data->philo_nbr)
		safe_thread_handle(&data->philos[i].thread_id, NULL, NULL, JOIN);
}
