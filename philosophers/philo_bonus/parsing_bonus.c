/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:42:02 by gaga              #+#    #+#             */
/*   Updated: 2025/11/04 22:36:35 by gaga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static inline bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static inline bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Only positive numbers should be passed.");
	if (!ft_isdigit(*str))
		error_exit("The input is not a correct digit");
	number = str;
	while (ft_isdigit(*str++))
		len++;
	if (len > 10)
		error_exit("The value is bigger than INT_MAX");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (ft_isdigit(*str))
		num = num * 10 + (*str++ - '0');
	if (num > INT_MAX)
		error_exit("The value is bigger than INT_MAX");
	return (num);
}

void	parse_input(t_data *data, char **av)
{
	data->philo_nbr = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]) * 1e3;
	data->time_to_eat = ft_atol(av[3]) * 1e3;
	data->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (data->time_to_die < 6e4 || data->time_to_eat < 6e4
		|| data->time_to_sleep < 6e4)
		error_exit("Use timestamps more than 60 miliseconds");
	if (av[5])
		data->nbr_meals_philo_can_eat = ft_atol(av[5]);
	else
		data->nbr_meals_philo_can_eat = -1;
}
