/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:52:46 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/20 20:11:35 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_types.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static void	handle_word(t_tokctx *ctx, const char *input, size_t *i, size_t len)
{
	size_t	start;
	char	*val;

	start = *i;
	while (*i < len && !isspace(input[*i]) && !is_operator_char(input[*i])
		&& input[*i] != '(' && input[*i] != ')')
		(*i)++;
	val = ft_strndup(input + start, *i - start);
	token_chainer(ctx, TOKEN_WORD, val, QUOTE_NONE);
}

int	handle_parentheses_case(t_tokctx *ctx, const char *input, size_t *i)
{
	if (input[*i] == '(' || input[*i] == ')')
	{
		if (input[*i] == '(')
			token_chainer(ctx, TOKEN_LPAREN, ft_strdup("("), QUOTE_NONE);
		else
			token_chainer(ctx, TOKEN_RPAREN, ft_strdup(")"), QUOTE_NONE);
		(*i)++;
		return (1);
	}
	return (0);
}

static int	handle_whitespace(const char *input, size_t *i, size_t len)
{
	while (*i < len && isspace(input[*i]))
		(*i)++;
	return (*i < len);
}

static void	tokenize_loop(t_tokctx *ctx, const char *input, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (!handle_whitespace(input, &i, len))
			break ;
		if (handle_parentheses_case(ctx, input, &i))
			continue ;
		if (handle_operator_case(ctx, input, &i))
			continue ;
		if (handle_quote_case(ctx, input, &i, len))
			continue ;
		handle_word(ctx, input, &i, len);
	}
}

t_token	*tokenize(const char *input)
{
	t_tokctx	ctx;
	size_t		len;

	ctx.head = NULL;
	ctx.tail = NULL;
	len = ft_strlen(input);
	tokenize_loop(&ctx, input, len);
	return (ctx.head);
}
