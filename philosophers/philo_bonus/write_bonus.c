/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:51:57 by gaga              #+#    #+#             */
/*   Updated: 2025/11/05 16:47:56 by gaga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	write_status_debug(t_philo_status status, t_philo *philo,
		long elapsed)
{
	if (TAKE_FORK == status && !simulation_finished(philo->data))
		printf(WHITE "%-6ld" RST BLUE " %d has taken fork 🍽️\n", elapsed,
			philo->id);
	else if (EATING == status && !simulation_finished(philo->data))
		printf(WHITE "%-6ld" RST CYAN " %d is eating 🍝"
						"\t\t\t" YELLOW "[🍝 %ld 🍝]\n" RST,
				elapsed,
				philo->id,
				philo->meals_counter);
	else if (SLEEPING == status && !simulation_finished(philo->data))
		printf(WHITE "%-6ld" RST " %d is sleeping 💤\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->data))
		printf(WHITE "%-6ld" RST " %d is thinking 🤔\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED "\t\t💀💀💀 %-6ld %d died 💀💀💀\n" RST, elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILISECOND) - philo->data->start_simulation_time;
	if (philo->full)
		return ;
	safe_semaphore_handle(&philo->data->write_semaphore, WAIT, 0);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if (TAKE_FORK == status && !simulation_finished(philo->data))
			printf(WHITE "%-6ld" RST " %d has taken a fork\n", elapsed,
				philo->id);
		else if (EATING == status && !simulation_finished(philo->data))
			printf(WHITE "%-6ld" RST CYAN " %d is eating\n" RST, elapsed,
				philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->data))
			printf(WHITE "%-6ld" RST " %d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status && !simulation_finished(philo->data))
			printf(WHITE "%-6ld" RST " %d is thinking\n", elapsed, philo->id);
		else if (DIED == status)
			printf(RED "%-6ld %d died\n" RST, elapsed, philo->id);
	}
	safe_semaphore_handle(&philo->data->write_semaphore, POST, 0);
}
