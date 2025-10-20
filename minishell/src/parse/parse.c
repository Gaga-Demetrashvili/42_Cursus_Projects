/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:25:22 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/20 20:12:00 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_types.h"

static t_ast	*parse_and_or(t_token **cur);

static t_ast	*parse_command(t_token **cur)
{
	t_ast	*node;
	t_cmd	*cmd;

	cmd = create_cmd();
	if (*cur && (*cur)->type == TOKEN_LPAREN)
	{
		*cur = (*cur)->next;
		node = parse_and_or(cur);
		if (*cur && (*cur)->type == TOKEN_RPAREN)
			*cur = (*cur)->next;
		free(cmd);
		return (node);
	}
	cmd->argv = build_argv(cur);
	parse_redirection(cur, cmd);
	return (create_command_node(cmd));
}

static t_ast	*parse_pipe(t_token **cur)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_command(cur);
	while (*cur && (*cur)->type == TOKEN_PIPE)
	{
		*cur = (*cur)->next;
		right = parse_command(cur);
		left = create_operator_node(left, right, TOKEN_PIPE);
	}
	return (left);
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
			left = create_operator_node(left, right, TOKEN_AND);
		else
			left = create_operator_node(left, right, TOKEN_OR);
	}
	return (left);
}

t_ast	*parse(t_token *tokens)
{
	t_token	*cur;
	t_ast	*tree;

	cur = tokens;
	tree = parse_and_or(&cur);
	return (tree);
}
