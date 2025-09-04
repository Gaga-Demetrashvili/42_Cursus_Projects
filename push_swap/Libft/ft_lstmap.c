/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:13:47 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/20 11:28:00 by gdemetra         ###   ########.fr       */
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

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*curr_node;
	char	*new_node_content;
	t_list	*new_lst;
	t_list	*new_lst_curr;

	curr_node = lst;
	new_lst = ft_lstnew(NULL);
	new_lst_curr = new_lst;
	while (curr_node)
	{
		new_node_content = f(curr_node->content);
		if (!new_lst_curr)
		{
			del(new_node_content);
			return (NULL);
		}
		new_lst_curr->content = new_node_content;
		curr_node = curr_node->next;
		if (curr_node)
		{
			new_lst_curr->next = ft_lstnew(NULL);
			new_lst_curr = new_lst_curr->next;
		}
	}
	return (new_lst);
}

void	*ft_delegate(void *content)
{
	return (ft_strdup((char *)content));
}

void	ft_del_content(void *content)
{
	free(content);
}

// int	main(void)
// {
// 	t_list	*begin;
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;
// 	t_list	*res;

// 	begin = NULL;
// 	node1 = ft_lstnew((void *)ft_strdup("First "));
// 	node2 = ft_lstnew((void *)ft_strdup("Second "));
// 	node3 = ft_lstnew((void *)ft_strdup("Third "));
// 	ft_lstadd_back(&begin, node1);
// 	ft_lstadd_back(&begin, node2);
// 	ft_lstadd_back(&begin, node3);
// 	ft_print_list_t(begin);
// 	res = ft_lstmap(begin, ft_delegate, ft_del_content);
// 	ft_printf("\n");
// 	ft_print_list_t(res);
// 	return (0);
// }
