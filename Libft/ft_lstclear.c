/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:38:00 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/19 20:06:37 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr_node;
	t_list	*prev_node;

	curr_node = *lst;
	while (curr_node)
	{
		prev_node = curr_node;
		curr_node = curr_node->next;
		ft_lstdelone(prev_node, del);
	}
	*lst = NULL;
}

// void	ft_del_content(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_list	*begin;
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;

// 	begin = NULL;
// 	node1 = ft_lstnew((void *)ft_strdup("First "));
// 	node2 = ft_lstnew((void *)ft_strdup("Second "));
// 	node3 = ft_lstnew((void *)ft_strdup("Third"));
// 	ft_lstadd_back(&begin, node1);
// 	ft_lstadd_back(&begin, node2);
// 	ft_lstadd_back(&begin, node3);
//     printf("%s\n", (char *)node1->content);
//     printf("%s\n", (char *)node2->content);
//     printf("%s\n", (char *)node3->content);
//     printf("begin content: %s\n", (char *)begin->content);
// 	ft_lstclear(&begin, ft_del_content);
//     if (!begin)
//         printf("Begin became null");
// 	return (0);
// }
