/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:51:02 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/17 21:51:02 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*curr_node;

	if (!lst)
		return (NULL);
	curr_node = lst;
	while (curr_node->next)
	{
		curr_node = curr_node->next;
	}
	return (curr_node);
}

// int	main(void)
// {
// 	t_list	*head;
// 	char	*data1;
// 	char	*data2;
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*last_node;

// 	head = NULL;
// 	data1 = " First";
// 	data2 = "Second";
// 	node1 = ft_lstnew((void *)data1);
// 	node2 = ft_lstnew((void *)data2);
// 	ft_lstadd_front(&head, node1);
// 	ft_lstadd_front(&head, node2);
// 	last_node = ft_lstlast(head);
// 	ft_printf("%s", (char *)last_node->content);
// 	free(node1);
// 	free(node2);
// 	return (0);
// }
