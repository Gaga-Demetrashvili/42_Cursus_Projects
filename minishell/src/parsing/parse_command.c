/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"

t_ast	*handle_parentheses(t_token **cur, t_ast *(*parse_fn)(t_token **))
{
	t_ast	*node;

	*cur = (*cur)->next;
	node = parse_fn(cur);
	if (*cur && (*cur)->type == TOKEN_RPAREN)
		*cur = (*cur)->next;
	return (node);
}

static t_ast	*build_cmd_node(char **argv, t_token **cur)
{
	char	*infile;
	char	*outfile;
	char	*heredoc;
	int		append;
	t_ast	*node;

	infile = NULL;
	outfile = NULL;
	heredoc = NULL;
	append = get_append_from_tokens(*cur);
	handle_redirections(cur, &infile, &outfile, &heredoc);
	node = create_command_node(argv, infile, outfile, append);
	set_command_heredoc(node, heredoc);
	return (node);
}

t_ast	*parse_command(t_token **cur, t_ast *(*parse_fn)(t_token **))
{
	char	**argv;

	if (*cur && (*cur)->type == TOKEN_LPAREN)
		return (handle_parentheses(cur, parse_fn));
	argv = build_argv(cur);
	return (build_cmd_node(argv, cur));
}
