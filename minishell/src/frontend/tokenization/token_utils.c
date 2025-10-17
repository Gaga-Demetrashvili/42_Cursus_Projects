/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:42:52 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 17:40:23 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell_types.h"

void	dup_and_add(t_token **head, t_token **tail, t_token *src)
{
	add_token(head, tail, new_token(src->type, strdup(src->value), src->quote));
}

void	add_token(t_token **head, t_token **tail, t_token *new_tok)
{
	if (!*head)
		*head = new_tok;
	else
		(*tail)->next = new_tok;
	*tail = new_tok;
}

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
