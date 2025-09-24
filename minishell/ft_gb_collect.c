/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gb_collect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:35:51 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/31 20:03:57 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gb_collect.h"

t_gc	*init_gc(t_gc *initial_gc)
{
	static t_gc	*gc;

	if (NULL == initial_gc)
		return (gc);
	initial_gc->head = NULL;
	gc = initial_gc;
	return (gc);
}

t_gc	*ft_gc(void)
{
	return (init_gc(NULL));
}

void	gc_free_all(void)
{
	t_gc_node	*tmp;
	t_gc		*gc;

	gc = ft_gc();
	while (gc->head)
	{
		tmp = gc->head->next;
		free(gc->head->ptr);
		free(gc->head);
		gc->head = tmp;
	}
	free(ft_gc());
}

void	*gc_malloc(size_t size)
{
	void		*ptr;
	t_gc_node	*node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = malloc(sizeof(t_gc_node));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = ft_gc()->head;
	ft_gc()->head = node;
	return (ptr);
}

void	gc_free(void *ptr)
{
	t_gc		*gc;
	t_gc_node	*prev;
	t_gc_node	*curr;

	prev = NULL;
	gc = ft_gc();
	curr = gc->head;
	while (curr)
	{
		if (curr->ptr == ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				gc->head = curr->next;
			free(curr->ptr);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
