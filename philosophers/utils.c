/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:51:40 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/30 22:32:37 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

static int	is_numeric(char *str_num)
{
	int	i;

	if (!str_num)
		return (1);
	i = 0;
	while (str_num[i])
	{
		if (str_num[i] < '0' || str_num[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_atoi(const char *str_num)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (str_num[i])
	{
		num = num * 10 + (str_num[i] - '0');
		i++;
	}
	return (num);
}

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->args[NUM_OF_PHILOS]);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->args[NUM_OF_PHILOS])
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (i--)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

void	cleanup_mutexes(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->args[NUM_OF_PHILOS])
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
	}
	free(data->forks);
}

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

int	args_validation_and_initialization(int ac, char **argv, int *args,
		int num_of_args)
{
	int	i;

	if (num_of_args < 4 || num_of_args > 5)
	{
		printf("Error! Program takes 4 or 5 arguments\n");
		return (1);
	}
	i = 0;
	while (i < num_of_args)
	{
		if (is_numeric(argv[i + 1]))
		{
			printf("Error! Make sure to pass valid positive numbers\n");
			return (2);
		}
		args[i] = ft_atoi(argv[i + 1]);
		if (i < num_of_args - 1 && args[i] == 0)
		{
			printf("Error! First 4 args should be more than 0\n");
			return (3);
		}
		i++;
	}
	return (0);
}
