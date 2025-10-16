/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parenthesis_case.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:48:44 by gaga              #+#    #+#             */
/*   Updated: 2025/10/16 22:49:20 by gaga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"

static void	handle_parentheses(t_tokctx *ctx, char paren)
{
	if (paren == '(')
		token_chainer(ctx, TOKEN_LPAREN, strdup("("), QUOTE_NONE);
	else
		token_chainer(ctx, TOKEN_RPAREN, strdup(")"), QUOTE_NONE);
}

int	handle_parentheses_case(t_tokctx *ctx, const char *input, size_t *i)
{
	if (input[*i] == '(' || input[*i] == ')')
	{
		handle_parentheses(ctx, input[*i]);
		(*i)++;
		return (1);
	}
	return (0);
}
