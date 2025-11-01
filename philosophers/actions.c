/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:58:03 by gdemetra          #+#    #+#             */
/*   Updated: 2025/11/01 19:39:05 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	taking_forks_logic(t_philo *philo)
{
	int	res;

	res = 0;
	if (philo->id % 2 == 0)
		res = taking_fork_for_even_numbered_philo(philo);
	else
		res = taking_fork_for_odd_numbered_philo(philo);
	return (res);
}

void	eating(t_philo *philo, int iteration)
{
	if (taking_forks_logic(philo))
		return ;
	if (check_if_it_is_time_to_die(philo, iteration))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	if (check_simulation_stop(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	print_action(philo, "is eating");
	philo->last_meal_time = get_timestamp();
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	sleeping(t_philo *philo, int iteration)
{
	if (check_if_it_is_time_to_die(philo, iteration))
		return (1);
	if (check_simulation_stop(philo))
		return (1);
	print_action(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
	return (0);
}

int	thinking(t_philo *philo, int iteration)
{
	if (check_if_it_is_time_to_die(philo, iteration))
		return (1);
	if (check_simulation_stop(philo))
		return (1);
	print_action(philo, "is thinking");
	return (0);
}
