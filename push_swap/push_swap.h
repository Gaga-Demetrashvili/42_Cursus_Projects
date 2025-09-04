/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:10:28 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/11 17:57:06 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "Libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_stack
{
	int		*arr;
	int		size;
	int		capacity;
	char	name;
	void	(*swap)(struct s_stack *self);
	void	(*rotate)(struct s_stack *self);
	void	(*rrotate)(struct s_stack *self);
}			t_stack;

// validation part
int			*validate_input(char **args, int size);

// utils
void		print_int_arr(int *arr, int size);
void		print_both_stacks(t_stack *stack_a, t_stack *stack_b);
int			*sort_and_indexsize_int_tab(int *arr, int size);
int			splitted_args_size(char **args);
void		radix_sort(t_stack *a, t_stack *b);
size_t		ascending(int a, int b);
int			indexsize_arr(int *indexed_arr, int *arr, int size);
int			*arrdup(int *arr, int size);
void		sort_three(t_stack *a);
void		sort_five(t_stack *a, t_stack *b);

// stack operations part
t_stack		*create_stack(int *arr, int size, int capacity, char name);
void		swap(t_stack *stack);
void		rotate(t_stack *stack);
void		rrotate(t_stack *stack);
void		push(t_stack *a, t_stack *b);

// stack operations utils part
void		shift_elements(t_stack *stack, size_t dir);

// I think main sorting logic will go here (might rename file and method later)
void		push_swap(int size, char **argv);

// method for testing if operations work properly
void		stack_operations_tests(t_stack *stack_a, t_stack *stack_b);

#endif