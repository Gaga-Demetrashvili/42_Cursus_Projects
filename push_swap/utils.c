/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:10:43 by gdemetra          #+#    #+#             */
/*   Updated: 2025/07/24 17:12:55 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	ascending(int a, int b)
{
	return (a <= b);
}

int	*arrdup(int *arr, int size)
{
	int	*new_arr;
	int	i;

	new_arr = malloc(sizeof(int) * size);
	if (!new_arr || !arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_arr[i] = arr[i];
		i++;
	}
	return (new_arr);
}

static int	get_index(int *sorted_arr, int val, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (sorted_arr[i] == val)
			return (i);
		i++;
	}
	return (-1);
}

int	indexsize_arr(int *indexed_arr, int *arr, int size)
{
	int	i;
	int	index;

	i = 0;
	while (i < size)
	{
		index = get_index(arr, indexed_arr[i], size);
		if (index == -1)
			return (0);
		indexed_arr[i] = index;
		i++;
	}
	return (1);
}

int	splitted_args_size(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
