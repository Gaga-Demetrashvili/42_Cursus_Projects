/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:42:52 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/16 22:44:33 by gaga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"

t_token	*new_token(t_token_type type, char *value, t_quote_type quote)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	tok->quote = quote;
	tok->next = NULL;
	return (tok);
}

void	token_chainer(t_tokctx *ctx, t_token_type type, char *value,
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
