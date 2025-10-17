/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:43:59 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/08 20:19:33 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"

// -------------------------
// Create a command node
// -------------------------
t_ast	*create_command_node(char **argv, char *infile, char *outfile,
		int append, char *heredoc)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = TOKEN_WORD;
	node->argv = argv;
	node->left = NULL;
	node->right = NULL;
	node->infile = infile;
	node->outfile = outfile;
	node->append = append;
	node->heredoc = heredoc;
	return (node);
}

// -------------------------
// Create an AND (&&) node
// -------------------------
t_ast	*create_and_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = TOKEN_AND;
	node->argv = NULL;
	node->left = left;
	node->right = right;
	node->infile = NULL;
	node->outfile = NULL;
	node->append = 0;
	node->heredoc = NULL;
	return (node);
}

// -------------------------
// Create an OR (||) node
// -------------------------
t_ast	*create_or_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = TOKEN_OR;
	node->argv = NULL;
	node->left = left;
	node->right = right;
	node->infile = NULL;
	node->outfile = NULL;
	node->append = 0;
	node->heredoc = NULL;
	return (node);
}

// -------------------------
// Optional: Create a PIPE (|) node
// -------------------------
t_ast	*create_pipe_node(t_ast *left, t_ast *right)
{
	t_ast *node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);

	node->type = TOKEN_PIPE;
	node->argv = NULL;
	node->left = left;
	node->right = right;
	node->infile = NULL;
	node->outfile = NULL;
	node->append = 0;
	node->heredoc = NULL;

	return (node);
}