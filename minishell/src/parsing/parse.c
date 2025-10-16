/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"

static t_ast	*parse_and_or(t_token **cur);
static t_ast	*parse_pipe(t_token **cur);

t_ast	*parse(t_token *tokens)
{
	t_token	*cur;
	t_ast	*tree;

	cur = tokens;
	tree = parse_and_or(&cur);
	return (tree);
}

static t_ast	*parse_and_or(t_token **cur)
{
	t_ast			*left;
	t_token_type	op;
	t_ast			*right;

	left = parse_pipe(cur);
	while (*cur && ((*cur)->type == TOKEN_AND || (*cur)->type == TOKEN_OR))
	{
		op = (*cur)->type;
		*cur = (*cur)->next;
		right = parse_pipe(cur);
		if (op == TOKEN_AND)
			left = create_and_node(left, right);
		else
			left = create_or_node(left, right);
	}
	return (left);
}

static t_ast	*parse_pipe(t_token **cur)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_command(cur, parse_and_or);
	while (*cur && (*cur)->type == TOKEN_PIPE)
	{
		*cur = (*cur)->next;
		right = parse_command(cur, parse_and_or);
		left = create_pipe_node(left, right);
	}
	return (left);
}
