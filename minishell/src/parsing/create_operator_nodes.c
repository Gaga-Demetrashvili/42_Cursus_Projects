/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_operator_nodes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"

static void	init_operator_node(t_ast *node, t_token_type type,
				t_ast *left, t_ast *right)
{
	node->type = type;
	node->argv = NULL;
	node->left = left;
	node->right = right;
	node->infile = NULL;
	node->outfile = NULL;
	node->append = 0;
	node->heredoc = NULL;
}

t_ast	*create_and_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	init_operator_node(node, TOKEN_AND, left, right);
	return (node);
}

t_ast	*create_or_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	init_operator_node(node, TOKEN_OR, left, right);
	return (node);
}

t_ast	*create_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	init_operator_node(node, TOKEN_PIPE, left, right);
	return (node);
}
