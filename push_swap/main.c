/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:09:44 by gdemetra          #+#    #+#             */
/*   Updated: 2025/07/24 23:09:22 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_array(void **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	main(int argc, char **argv)
{
	int	size;
	int	need_free;

	need_free = 0;
	if (argc == 1 || (2 == argc && !argv[1][0]))
		return (0);
	if (2 == argc)
	{
		need_free = 1;
		argv = ft_split(argv[1], ' ');
		size = splitted_args_size(argv);
	}
	else
	{
		argv = argv + 1;
		size = argc - 1;
	}
	push_swap(size, argv);
	if (need_free)
		free_array((void **)argv, size);
	return (0);
}
