/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote_case.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:47:46 by gaga              #+#    #+#             */
/*   Updated: 2025/10/20 20:11:51 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_types.h"

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
	val = ft_strndup(input + start, *i - start);
	if (quote == '\'')
		quote_type = QUOTE_SINGLE;
	else
		quote_type = QUOTE_DOUBLE;
	token_chainer(ctx, TOKEN_WORD, val, quote_type);
	if (*i < len)
		(*i)++;
}

int	handle_quote_case(t_tokctx *ctx, const char *input, size_t *i, size_t len)
{
	if (input[*i] == '\'' || input[*i] == '"')
	{
		handle_quoted_string(ctx, input, i, len);
		return (1);
	}
	return (0);
}
