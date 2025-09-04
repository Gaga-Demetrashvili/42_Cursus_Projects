/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:19:38 by gdemetra          #+#    #+#             */
/*   Updated: 2025/07/24 16:19:39 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	shift_elements(t_stack *stack, size_t dir)
{
	int	i;

	if (dir)
	{
		i = 1;
		while (i < stack->size)
		{
			stack->arr[i - 1] = stack->arr[i];
			i++;
		}
	}
	else
	{
		if (stack->size == 0)
			return ;
		i = stack->size - 1;
		while (i >= 0)
		{
			stack->arr[i + 1] = stack->arr[i];
			i--;
		}
	}
}
