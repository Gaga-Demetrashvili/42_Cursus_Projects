/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:59:49 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"
#include <stdio.h>

static int	execute_and(t_ast *node)
{
	int	ls;

	ls = execute(node->left);
	if (ls == 0)
		return (execute(node->right));
	if (ls)
		return (1);
	return (0);
}

static int	execute_or(t_ast *node)
{
	int	ls;

	ls = execute(node->left);
	if (ls != 0)
		return (execute(node->right));
	return (0);
}

static int	handle_token_pipe(t_ast *node)
{
	return (execute_pipe(node));
}

static int	handle_token_word(t_ast *node)
{
	return (execute_command(node));
}

int	execute(t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == TOKEN_PIPE)
		return (handle_token_pipe(node));
	if (node->type == TOKEN_AND)
		return (execute_and(node));
	if (node->type == TOKEN_OR)
		return (execute_or(node));
	if (node->type == TOKEN_WORD)
		return (handle_token_word(node));
	fprintf(stderr, "Unsupported AST node type: %d\n", node->type);
	return (1);
}
