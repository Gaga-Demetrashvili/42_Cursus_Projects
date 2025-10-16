/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"

static int	is_redir_token(t_token *tok)
{
	return (tok && (tok->type == TOKEN_REDIR_IN
			|| tok->type == TOKEN_REDIR_OUT || tok->type == TOKEN_APPEND
			|| tok->type == TOKEN_HEREDOC));
}

static void	process_redir(t_token_type redir, char *value,
				char **infile, char **outfile)
{
	if (redir == TOKEN_REDIR_IN)
		*infile = strdup(value);
	else if (redir == TOKEN_REDIR_OUT || redir == TOKEN_APPEND)
		*outfile = strdup(value);
}

static int	get_append_flag(t_token_type redir, int current)
{
	if (redir == TOKEN_REDIR_OUT)
		return (0);
	else if (redir == TOKEN_APPEND)
		return (1);
	return (current);
}

void	handle_redirections(t_token **cur, char **infile,
			char **outfile, char **heredoc)
{
	t_token_type	redir;

	while (is_redir_token(*cur))
	{
		redir = (*cur)->type;
		*cur = (*cur)->next;
		if (*cur && (*cur)->type == TOKEN_WORD)
		{
			if (redir == TOKEN_HEREDOC)
				*heredoc = strdup((*cur)->value);
			else
				process_redir(redir, (*cur)->value, infile, outfile);
			*cur = (*cur)->next;
		}
	}
}

int	get_append_from_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_APPEND)
			return (1);
		else if (tokens->type == TOKEN_REDIR_OUT)
			return (0);
		tokens = tokens->next;
	}
	return (0);
}
