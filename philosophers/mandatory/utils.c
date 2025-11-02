/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:31:00 by gaga              #+#    #+#             */
/*   Updated: 2025/11/02 23:38:18 by gaga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if (SECOND == time_code)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else if (MILISECOND == time_code)
		return (tv.tv_sec / 1e3 + tv.tv_usec * 1e3);
	else if (MICROSECOND == time_code)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else
		error_exit("Wrong input to gettime!");
	return (1337);
}

void	error_exit(const char *error)
{
	printf(RED "Error!\n%s\n" RST, error);
	exit(EXIT_FAILURE);
}