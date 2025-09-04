/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:10:45 by gdemetra          #+#    #+#             */
/*   Updated: 2025/07/24 16:51:01 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_arg_int(char *arg)
{
	size_t	i;

	if (arg[0] == '0' && arg[1] != '\0')
		return (0);
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '-' && (i != 0 || arg[1] == '\0'))
			return (0);
		if (arg[i] != '-' && (arg[i] < '0' || arg[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

static int	num_sits_in_int_limit(long num)
{
	if (num < INT_MIN || num > INT_MAX)
		return (0);
	return (1);
}

static int	is_distinct(int *arr, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i != j && arr[i] == arr[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	validate_and_init_arr(int **arr, char **args, int size)
{
	int	i;

	if (!args || size == 0)
	{
		*arr = NULL;
		return ;
	}
	*arr = (int *)malloc(sizeof(int) * size);
	if (!arr)
		return ;
	i = 0;
	while (i < size)
	{
		if (is_arg_int(args[i]) && num_sits_in_int_limit(ft_atoi(args[i])))
			(*arr)[i] = ft_atoi(args[i]);
		else
		{
			free(*arr);
			*arr = NULL;
			return ;
		}
		i++;
	}
}

int	*validate_input(char **args, int size)
{
	int	*arr;
	int	distinct;

	validate_and_init_arr(&arr, args, size);
	if (!arr)
		return (NULL);
	distinct = is_distinct(arr, size);
	if (!distinct)
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}
