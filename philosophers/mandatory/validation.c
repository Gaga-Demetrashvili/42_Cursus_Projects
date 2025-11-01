/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:55:56 by gdemetra          #+#    #+#             */
/*   Updated: 2025/11/01 23:34:08 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static int	ft_atoi_long_long(const char *str_num)
{
	long long	num;
	int			i;

	num = 0;
	i = 0;
	while (str_num[i])
	{
		num = num * 10 + (str_num[i] - '0');
		i++;
	}
	return (num);
}

static void	init_data(t_data *data, char **argv)
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi_long_long(argv[2]);
	data->time_to_eat = ft_atoi_long_long(argv[3]);
	data->time_to_sleep = ft_atoi_long_long(argv[4]);
	if (argv[5])
		data->num_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		data->num_of_times_each_philo_must_eat = 0;
	data->simulation_stop = 0;
}

int	args_validation_and_initialization(char **argv, t_data *data,
		int num_of_args)
{
	int	i;

	if (num_of_args < 4 || num_of_args > 5)
	{
		printf("Error! Program takes 4 or 5 arguments\n");
		return (3);
	}
	i = 0;
	while (i < num_of_args)
	{
		if (is_numeric(argv[i + 1]))
		{
			printf("Error! Make sure to pass valid positive numbers\n");
			return (4);
		}
		i++;
	}
	init_data(data, argv);
	if (data->num_of_philos == 0 || data->time_to_die == 0
		|| data->time_to_eat == 0 || data->time_to_sleep == 0)
	{
		printf("Error! 1st 4 args have to be more than zero\n");
		return (5);
	}
	return (0);
}
