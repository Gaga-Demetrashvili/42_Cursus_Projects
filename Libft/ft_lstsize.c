/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:45:24 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/17 20:45:24 by gdemetra         ###   ########.fr       */
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

size_t	ft_lstsize(t_list *lst)
{
	t_list	*curr_node;
	size_t	i;

	curr_node = lst;
	i = 0;
	while (curr_node)
	{
		i++;
		curr_node = curr_node->next;
	}
	return (i);
}

// int	main(void)
// {
// 	t_list	*head;
// 	char	*data1;
// 	char	*data2;
// 	char	*data3;
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;

// 	head = NULL;
// 	data1 = " First";
// 	data2 = " Second";
// 	data3 = "Third";
// 	node1 = ft_lstnew((void *)data1);
// 	node2 = ft_lstnew((void *)data2);
// 	node3 = ft_lstnew((void *)data3);
// 	ft_lstadd_front(&head, node1);
// 	ft_lstadd_front(&head, node2);
// 	ft_lstadd_front(&head, node3);
// 	// ft_print_list_t(head);
// 	printf("%zu", ft_lstsize(head));
// 	free(node1);
// 	free(node2);
// 	free(node3);
// 	return (0);
// }
