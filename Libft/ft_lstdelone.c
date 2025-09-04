/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:56:57 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/19 18:37:24 by gdemetra         ###   ########.fr       */
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

void	ft_del_node(void *content)
{
	free(content);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
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
// 	ft_lstdelone(node2, ft_del_node);
// 	ft_print_list_t(begin);
// 	free(node1);
// 	free(node2);
// 	free(node3);
// 	return (0);
// }
