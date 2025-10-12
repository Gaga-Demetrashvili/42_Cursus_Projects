/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:42:52 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/12 21:49:05 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	tok->quote = QUOTE_NONE;
	tok->next = NULL;
	return (tok);
}
