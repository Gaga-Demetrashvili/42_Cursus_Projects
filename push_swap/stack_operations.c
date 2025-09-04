/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:10:34 by gdemetra          #+#    #+#             */
/*   Updated: 2025/07/24 16:20:15 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_stack *a, t_stack *b)
{
	int	tmp;

	if (a->size == 0)
		return ;
	tmp = a->arr[0];
	if (a->size == 0 || b->size == b->capacity)
		return ;
	shift_elements(a, 1);
	a->size--;
	shift_elements(b, 0);
	b->size++;
	b->arr[0] = tmp;
	ft_printf("p%c\n", b->name);
}

void	rotate(t_stack *stack)
{
	int	tmp;

	tmp = stack->arr[0];
	shift_elements(stack, 1);
	stack->arr[stack->size - 1] = tmp;
	ft_printf("r%c\n", stack->name);
}

void	rrotate(t_stack *stack)
{
	int	tmp;

	tmp = stack->arr[stack->size - 1];
	stack->size--;
	shift_elements(stack, 0);
	stack->size++;
	stack->arr[0] = tmp;
	ft_printf("rr%c\n", stack->name);
}

void	swap(t_stack *stack)
{
	int	tmp;

	if (stack->size <= 1)
		return ;
	tmp = (stack->arr)[0];
	(stack->arr)[0] = (stack->arr)[1];
	(stack->arr)[1] = tmp;
	ft_printf("s%c\n", stack->name);
}

t_stack	*create_stack(int *arr, int size, int capacity, char name)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	stack->arr = arr;
	stack->size = size;
	stack->capacity = capacity;
	stack->name = name;
	stack->swap = swap;
	stack->rotate = rotate;
	stack->rrotate = rrotate;
	return (stack);
}
