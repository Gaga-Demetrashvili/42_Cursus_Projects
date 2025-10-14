/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:52:46 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/14 20:37:26 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static int	is_operator_char(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

static void	token_chainer(t_tokctx *ctx, t_token_type type, char *value,
		t_quote_type quote)
{
	t_token	*tok;

	tok = new_token(type, value, quote);
	tok->next = NULL;
	if (!ctx->head)
		ctx->head = tok;
	else
		ctx->tail->next = tok;
	ctx->tail = tok;
}

size_t	double_operator_matched(const char *input, size_t i, t_token_type *type)
{
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

// if 0 is returned than nothing was matched
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

static void	handle_parentheses(t_tokctx *ctx, char paren)
{
	if (paren == '(')
		token_chainer(ctx, TOKEN_LPAREN, strdup("("), QUOTE_NONE);
	else
		token_chainer(ctx, TOKEN_RPAREN, strdup(")"), QUOTE_NONE);
}

static void	handle_quoted_string(t_tokctx *ctx, const char *input, size_t *i,
		size_t len)
{
	size_t			start;
	char			quote;
	char			*val;
	t_quote_type	quote_type;

	quote = input[(*i)++];
	start = *i;
	while (*i < len && input[*i] != quote)
		(*i)++;
	val = strndup(input + start, *i - start);
	if (quote == '\'')
		quote_type = QUOTE_SINGLE;
	else
		quote_type = QUOTE_DOUBLE;
	token_chainer(ctx, TOKEN_WORD, val, quote_type);
	if (*i < len)
		(*i)++; // skip closing quote
}

static void	handle_word(t_tokctx *ctx, const char *input, size_t *i, size_t len)
{
	size_t	start;
	char	*val;

	start = *i;
	while (*i < len && !isspace(input[*i]) && !is_operator_char(input[*i])
		&& input[*i] != '(' && input[*i] != ')')
		(*i)++;
	val = strndup(input + start, *i - start);
	token_chainer(ctx, TOKEN_WORD, val, QUOTE_NONE);
}

t_token	*tokenize(const char *input)
{
	t_tokctx	ctx;
	size_t		i;
	size_t		len;
	size_t		op_len;

	ctx.head = NULL;
	ctx.tail = NULL;
	i = 0;
	len = strlen(input);
	op_len = 0;
	while (i < len)
	{
		// Skip whitespace
		while (i < len && isspace(input[i]))
			i++;
		if (i >= len)
			break ;
		// Parentheses
		if (input[i] == '(' || input[i] == ')')
		{
			handle_parentheses(&ctx, input[i]);
			i++;
			continue ;
		}
		// Operators
		if (is_operator_char(input[i]))
		{
			op_len = handle_operator(&ctx, input, i);
			if (!op_len)
				break ;
			i += op_len;
			continue ;
		}
		// Quoted strings
		if (input[i] == '\'' || input[i] == '"')
		{
			handle_quoted_string(&ctx, input, &i, len);
			continue ;
		}
		// Words (including wildcards)
		handle_word(&ctx, input, &i, len);
	}
	return (ctx.head);
}
