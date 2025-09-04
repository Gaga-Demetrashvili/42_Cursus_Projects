/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:37:32 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/17 20:42:29 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_print_list_t(t_list *node)
// {
// 	t_list	*curr_node;

// 	curr_node = node;
// 	while (curr_node)
// 	{
// 		ft_printf("%s", (char *)curr_node->content);
// 		curr_node = curr_node->next;
// 	}
// }

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new)
	{
		new->next = *lst;
		*lst = new;
	}
}

// int	main(void)
// {
// 	t_list	*head;
// 	char	*data1;
// 	char	*data2;
// 	t_list	*node1;
// 	t_list	*node2;

// 	head = NULL;
// 	data1 = " First";
// 	data2 = "Second";
// 	node1 = ft_lstnew((void *)data1);
// 	node2 = ft_lstnew((void *)data2);
// 	ft_lstadd_front(&head, node1);
// 	ft_lstadd_front(&head, node2);
// 	ft_print_list_t(head);
// 	free(node1);
// 	free(node2);
// 	return (0);
// }
