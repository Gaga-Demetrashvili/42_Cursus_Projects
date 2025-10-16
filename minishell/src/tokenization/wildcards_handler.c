/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

static int	expand_pattern_from_cwd(const char *pattern, int pat_starts_dot,
			t_token **new_head, t_token **new_tail)
{
	DIR				*dir;
	struct dirent	*entry;
	int				matched;

	dir = opendir(".");
	if (!dir)
		return (0);
	matched = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (!should_skip_name(entry->d_name, pat_starts_dot)
			&& match_star(pattern, entry->d_name))
		{
			add_token(new_head, new_tail, new_token(TOKEN_WORD,
					strdup(entry->d_name), QUOTE_NONE));
			matched = 1;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (matched);
}

static void	process_wildcard_token(t_token *cur, t_token **new_head,
				t_token **new_tail)
{
	int	pat_starts_dot;
	int	matched;

	if (!cur->value)
		return ;
	pat_starts_dot = (cur->value[0] == '.');
	matched = expand_pattern_from_cwd(cur->value, pat_starts_dot,
			new_head, new_tail);
	if (!matched)
		add_token(new_head, new_tail, new_token(TOKEN_WORD,
				strdup(cur->value), QUOTE_NONE));
}

static void	free_old_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

t_token	*expand_wildcards(t_token *tokens)
{
	t_token	*new_head;
	t_token	*new_tail;
	t_token	*cur;

	new_head = NULL;
	new_tail = NULL;
	cur = tokens;
	while (cur)
	{
		if (cur->type == TOKEN_WORD && cur->value && strchr(cur->value, '*'))
			process_wildcard_token(cur, &new_head, &new_tail);
		else
		{
			if (cur->value)
				add_token(&new_head, &new_tail, new_token(cur->type,
						strdup(cur->value), cur->quote));
			else
				add_token(&new_head, &new_tail, new_token(cur->type,
						NULL, cur->quote));
		}
		cur = cur->next;
	}
	free_old_tokens(tokens);
	return (new_head);
}
