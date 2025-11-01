/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:46:37 by gdemetra          #+#    #+#             */
/*   Updated: 2025/11/01 22:00:57 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	taking_fork_for_even_numbered_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (check_simulation_stop(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	if (check_simulation_stop(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_action(philo, "has taken a fork");
	return (0);
}

int	taking_fork_for_odd_numbered_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (check_simulation_stop(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	if (check_simulation_stop(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_action(philo, "has taken a fork");
	return (0);
}

void	print_action(t_philo *philo, const char *action)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", get_timestamp(), philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	report_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->simulation_stop)
	{
		philo->data->simulation_stop = 1;
		print_action(philo, "died");
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
}
