/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:51:40 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/30 16:13:51 by gdemetra         ###   ########.fr       */
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

int	args_validation_and_initialization(int ac, char **argv, int *args,
		int num_of_args)
{
	int	i;

	if (ac != num_of_args + 1)
	{
		printf("Error! Program takes exactly %d arguments\n", num_of_args);
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
		i++;
	}
	return (0);
}
