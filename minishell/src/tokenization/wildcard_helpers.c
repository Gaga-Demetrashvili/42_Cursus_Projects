/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"
#include <string.h>

void	add_token(t_token **head, t_token **tail, t_token *new_tok)
{
	if (!*head)
		*head = new_tok;
	else
		(*tail)->next = new_tok;
	*tail = new_tok;
}

int	match_star(const char *pattern, const char *s)
{
	const char	*star;
	size_t		blen;
	size_t		alen;
	size_t		s_len;

	star = strchr(pattern, '*');
	if (!star)
		return (strcmp(pattern, s) == 0);
	blen = (size_t)(star - pattern);
	alen = strlen(star + 1);
	s_len = strlen(s);
	if (blen && (s_len < blen || strncmp(s, pattern, blen) != 0))
		return (0);
	if (alen && (s_len < alen || strcmp(s + (s_len - alen), star + 1) != 0))
		return (0);
	if (s_len < blen + alen)
		return (0);
	return (1);
}

int	should_skip_name(const char *name, int pat_starts_dot)
{
	if (!pat_starts_dot && name[0] == '.')
		return (1);
	if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
		return (1);
	return (0);
}
