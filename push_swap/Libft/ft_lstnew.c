/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:28:06 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/17 20:28:06 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	if (!content)
		new_node->content = NULL;
	else
		new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

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

// int	main(void)
// {
// 	char node1_ct[] = "Gaga ";
// 	char node2_ct[] = "Demetrashvili ";
// 	char node3_ct[] = "gdemetra";
// 	t_list *node1 = ft_lstnew((void *)node1_ct);
// 	t_list *node2 = ft_lstnew((void *)node2_ct);
// 	t_list *node3 = ft_lstnew((void *)node3_ct);
// 	node1->next = node2;
// 	node2->next = node3;
// 	ft_print_list_t(node1);
// 	return (0);
// }