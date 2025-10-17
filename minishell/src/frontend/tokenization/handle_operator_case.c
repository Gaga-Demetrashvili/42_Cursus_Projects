/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator_case.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:40:58 by gaga              #+#    #+#             */
/*   Updated: 2025/10/17 16:50:48 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell_types.h"

size_t	double_operator_matched(const char *input, size_t i, t_token_type *type)
{
	if (input[i + 1] == '\0')
		return (0);
	if (input[i] == '|' && input[i + 1] == '|')
	{
		*type = TOKEN_OR;
		return (1);
	}
	if (input[i] == '&' && input[i + 1] == '&')
	{
		*type = TOKEN_AND;
		return (1);
	}
	if (input[i] == '<' && input[i + 1] == '<')
	{
		*type = TOKEN_HEREDOC;
		return (1);
	}
	if (input[i] == '>' && input[i + 1] == '>')
	{
		*type = TOKEN_APPEND;
		return (1);
	}
	return (0);
}

size_t	single_operator_matched(const char *input, size_t i, t_token_type *type)
{
	if (input[i] == '|')
	{
		*type = TOKEN_PIPE;
		return (1);
	}
	if (input[i] == '<')
	{
		*type = TOKEN_REDIR_IN;
		return (1);
	}
	if (input[i] == '>')
	{
		*type = TOKEN_REDIR_OUT;
		return (1);
	}
	return (0);
}

static size_t	handle_operator(t_tokctx *ctx, const char *input, size_t i)
{
	size_t			op_len;
	t_token_type	type;

	op_len = 0;
	if (double_operator_matched(input, i, &type))
		op_len = 2;
	else if (single_operator_matched(input, i, &type))
		op_len = 1;
	else
		return (0);
	token_chainer(ctx, type, strndup(input + i, op_len), QUOTE_NONE);
	return (op_len);
}

int	is_operator_char(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

int	handle_operator_case(t_tokctx *ctx, const char *input, size_t *i)
{
	size_t	op_len;

	if (is_operator_char(input[*i]))
	{
		op_len = handle_operator(ctx, input, *i);
		if (!op_len)
		{
			token_chainer(ctx, TOKEN_WORD, strndup(input + *i, 1), QUOTE_NONE);
			*i += 1;
			return (1);
		}
		*i += op_len;
		return (1);
	}
	return (0);
}
