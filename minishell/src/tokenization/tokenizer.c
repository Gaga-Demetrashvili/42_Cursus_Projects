/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:52:46 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/22 22:21:07 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_types.h"
#include <stdlib.h>
#include <string.h>

static int	is_whitespace_or_special(char c, int check_special)
{
	int	is_ws;

	is_ws = (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
			|| c == '\r');
	if (check_special)
		return (is_ws || is_operator_char(c) || c == '(' || c == ')');
	return (is_ws);
}

static void	handle_word(t_tokctx *ctx, const char *input, size_t *i, size_t len)
{
	size_t	start;
	char	*val;

	start = *i;
	while (*i < len && !is_whitespace_or_special(input[*i], 1))
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

static void	tokenize_loop(t_tokctx *ctx, const char *input, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		while (i < len && is_whitespace_or_special(input[i], 0))
			i++;
		if (i >= len)
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
