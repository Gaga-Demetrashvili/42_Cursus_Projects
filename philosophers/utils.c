/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:51:40 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/29 23:52:15 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_numeric(char *str_num)
{
	int	i;

	if (!str_num[i])
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

void	args_validation_and_initialization(int ac, char **argv, int **args,
		int num_of_args)
{
	int	i;

	if (ac != num_of_args + 1)
	{
		printf("Wrong number of arguments. Program takes exactly "
				"%d arguments\n",
				num_of_args);
		exit(1);
	}
	i = 0;
	while (args < num_of_args)
	{
		if (is_numeric(argv[i + 1]))
		{
			printf("Arg validation failed. Make sure to pass valid positive numbers\n");
			exit(2);
		}
		*args[i] = ft_atoi(argv[i + 1]);
	}
}
