#include "minishell_types.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

static void	add_token(t_token **head, t_token **tail, t_token *new_tok)
{
	if (!*head)
		*head = new_tok;
	else
		(*tail)->next = new_tok;
	*tail = new_tok;
}

// Single '*' support, prefix*suffix match
static int	match_star(const char *pattern, const char *s)
{
	const char	*star;
	char		before[256] = {0};
	char		after[256] = {0};
	size_t		blen;
	size_t		alen;
	size_t		slen;

	star = strchr(pattern, '*');
	if (!star)
		return (strcmp(pattern, s) == 0);
	strncpy(before, pattern, (size_t)(star - pattern));
	strcpy(after, star + 1);
	blen = strlen(before);
	alen = strlen(after);
	slen = strlen(s);
	if (blen && strncmp(s, before, blen) != 0)
		return (0);
	if (alen && (slen < alen || strcmp(s + slen - alen, after) != 0))
		return (0);
	if (slen < blen + alen)
		return (0);
	return (1);
}

t_token	*expand_wildcards(t_token *tokens)
{
	t_token *new_head;
	t_token *new_tail;
	t_token *cur;

	new_head = NULL;
	new_tail = NULL;
	cur = tokens;
	while (cur)
	{
		if (cur->type == TOKEN_WORD && strchr(cur->value, '*'))
		{
			DIR *dir;
			struct dirent *entry;
			int matched;
			int pat_starts_dot;

			dir = opendir(".");
			if (!dir)
			{
				add_token(&new_head, &new_tail, new_token(TOKEN_WORD,
						strdup(cur->value)));
				cur = cur->next;
				continue ;
			}
			matched = 0;
			pat_starts_dot = (cur->value[0] == '.');
			while ((entry = readdir(dir)))
			{
				if (!pat_starts_dot && entry->d_name[0] == '.')
					continue ;
				if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name,
						"..") == 0)
					continue ;
				if (match_star(cur->value, entry->d_name))
				{
					add_token(&new_head, &new_tail, new_token(TOKEN_WORD,
							strdup(entry->d_name)));
					matched = 1;
				}
			}
			closedir(dir);
			if (!matched)
				add_token(&new_head, &new_tail, new_token(TOKEN_WORD,
						strdup(cur->value)));
		}
		else
		{
			add_token(&new_head, &new_tail, new_token(cur->type,
					strdup(cur->value)));
			new_tail->quote = cur->quote;
		}
		cur = cur->next;
	}
	return (new_head);
}