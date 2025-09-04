/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:40:36 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/19 20:08:29 by gdemetra         ###   ########.fr       */
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

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*curr_node;

	curr_node = lst;
	while (curr_node)
	{
		f(curr_node->content);
		curr_node = curr_node->next;
	}
}

// void	ft_delegate(void *content)
// {
// 	*(char *)content += 1;
// }

// int	main(void)
// {
// 	t_list	*begin;
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;

// 	begin = NULL;
// 	node1 = ft_lstnew((void *)ft_strdup("0"));
// 	node2 = ft_lstnew((void *)ft_strdup("1"));
// 	node3 = ft_lstnew((void *)ft_strdup("2"));
// 	ft_lstadd_back(&begin, node1);
// 	ft_lstadd_back(&begin, node2);
// 	ft_lstadd_back(&begin, node3);
// 	ft_print_list_t(begin);
// 	ft_lstiter(begin, ft_delegate);
// 	ft_printf("\n");
// 	ft_print_list_t(begin);
// 	return (0);
// }
