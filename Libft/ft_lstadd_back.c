/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:44:02 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/18 22:01:33 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_print_list_t(t_list *node)
// {
// 	t_list	*curr_node;

// 	curr_node = node;
// 	while (curr_node)
// 	{
// 		printf("%s", (char *)curr_node->content);
// 		curr_node = curr_node->next;
// 	}
// }

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_n;

	if (new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			last_n = ft_lstlast(*lst);
			last_n->next = new;
		}
	}
}

// int	main(void)
// {
// 	t_list	*begin;
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;

// 	begin = NULL;
// 	node1 = ft_lstnew((void *)"First ");
// 	node2 = ft_lstnew((void *)"Second ");
// 	node3 = ft_lstnew((void *)"Third");
// 	ft_lstadd_back(&begin, node1);
// 	ft_lstadd_back(&begin, node2);
// 	ft_lstadd_back(&begin, node3);
// 	ft_print_list_t(begin);
// 	free(node1);
// 	free(node2);
// 	free(node3);
// 	return (0);
// }
