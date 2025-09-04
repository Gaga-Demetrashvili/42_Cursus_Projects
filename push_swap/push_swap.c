/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:10:22 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/11 17:56:50 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_mem(t_stack *a, t_stack *b)
{
	free(a->arr);
	free(b->arr);
	free(a);
	free(b);
}

int	check_arr(int *arr)
{
	if (!arr)
	{
		ft_printf("%s\n", "Error");
		return (1);
	}
	return (0);
}

int	arr_is_sorted(int *arr, int size)
{
	int	i;

	i = 1;
	while (i < size)
	{
		if (!ascending(arr[i - 1], arr[i]))
			return (0);
		i++;
	}
	return (1);
}

void	sort_mediator(int size, t_stack *a, t_stack *b)
{
	if (size == 3)
		sort_three(a);
	else if (size == 5)
		sort_five(a, b);
	else
		radix_sort(a, b);
}

void	push_swap(int size, char **argv)
{
	int		*arr;
	int		*indexed_arr;
	int		*arr_b;
	t_stack	*stack_a;
	t_stack	*stack_b;

	arr = validate_input(argv, size);
	if (check_arr(arr) || arr_is_sorted(arr, size))
		return ;
	indexed_arr = sort_and_indexsize_int_tab(arr, size);
	free(arr);
	if (check_arr(indexed_arr))
		return ;
	if (1 == size)
	{
		free(indexed_arr);
		return ;
	}
	arr_b = (int *)malloc(sizeof(int) * size);
	stack_a = create_stack(indexed_arr, size, size, 'a');
	stack_b = create_stack(arr_b, 0, size, 'b');
	sort_mediator(size, stack_a, stack_b);
	free_mem(stack_a, stack_b);
}
