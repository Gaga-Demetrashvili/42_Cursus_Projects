/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:33:07 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 17:45:06 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell_types.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

static int	match_star(const char *pat, const char *s)
{
	const char	*star;
	size_t		pfx;
	size_t		sfx;
	size_t		slen;

	star = strchr(pat, '*');
	if (!star)
		return (strcmp(pat, s) == 0);
	pfx = (size_t)(star - pat);
	sfx = strlen(star + 1);
	slen = strlen(s);
	if (pfx && strncmp(s, pat, pfx) != 0)
		return (0);
	if (slen < pfx + sfx)
		return (0);
	if (sfx && strcmp(s + slen - sfx, star + 1) != 0)
		return (0);
	return (1);
}

static int	should_include(const char *name, int pat_starts_dot)
{
	if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
		return (0);
	if (!pat_starts_dot && name[0] == '.')
		return (0);
	return (1);
}

static int	process_dir_entries(DIR *dir, t_token **head, t_token **tail,
		t_token *cur)
{
	struct dirent	*ent;
	int				matched;
	int				pat_dot;

	matched = 0;
	pat_dot = (cur->value && cur->value[0] == '.');
	ent = readdir(dir);
	while (ent)
	{
		if (!should_include(ent->d_name, pat_dot))
		{
			ent = readdir(dir);
			continue ;
		}
		if (match_star(cur->value, ent->d_name))
		{
			add_token(head, tail, new_token(TOKEN_WORD, strdup(ent->d_name),
					QUOTE_NONE));
			matched = 1;
		}
		ent = readdir(dir);
	}
	return (matched);
}

static void	expand_pattern_token(t_token **head, t_token **tail, t_token *cur)
{
	DIR	*dir;
	int	matched;

	dir = opendir(".");
	if (!dir)
		return (dup_and_add(head, tail, cur));
	matched = process_dir_entries(dir, head, tail, cur);
	closedir(dir);
	if (!matched)
		dup_and_add(head, tail, cur);
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
		if (cur->type == TOKEN_WORD && cur->quote == QUOTE_NONE && cur->value
			&& strchr(cur->value, '*'))
			expand_pattern_token(&new_head, &new_tail, cur);
		else
			dup_and_add(&new_head, &new_tail, cur);
		cur = cur->next;
	}
	return (new_head);
}
