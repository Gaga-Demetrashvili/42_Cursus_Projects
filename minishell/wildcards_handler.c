#include "minishell_types.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

// Helper: add token to list
static void	add_token(t_token **head, t_token **tail, t_token *new_tok)
{
	if (!*head)
		*head = new_tok;
	else
		(*tail)->next = new_tok;
	*tail = new_tok;
}

// Simple wildcard match for '*'
static int	match_star(const char *pattern, const char *str)
{
	const char	*p = pattern;
	const char	*s = str;
	char		before[128] = {0}, after[128] = {0};
	char		*star;
	size_t		blen;
	size_t		alen;
	size_t		slen;

	blen = strlen(before);
	alen = strlen(after);
	slen = 0;
	// Only support one '*' for simplicity
	star = strchr(p, '*');
	if (!star)
		return (strcmp(p, s) == 0);
	strncpy(before, p, star - p);
	strcpy(after, star + 1);
	blen = strlen(before), alen = strlen(after), slen = strlen(s);
	if (blen && strncmp(s, before, blen) != 0)
		return (0);
	if (alen && slen >= alen && strcmp(s + slen - alen, after) != 0)
		return (0);
	return (1);
}

// Main wildcard expansion function
t_token	*expand_wildcards(t_token *tokens)
{
	t_token *new_head = NULL, *new_tail = NULL;
	t_token *cur = tokens;
	while (cur)
	{
		if (cur->type == TOKEN_WORD && strchr(cur->value, '*'))
		{
			DIR *dir = opendir(".");
			if (dir)
			{
				struct dirent *entry;
				int matched = 0;
				while ((entry = readdir(dir)))
				{
					// Skip "." and ".."
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
				add_token(&new_head, &new_tail, new_token(TOKEN_WORD,
						strdup(cur->value)));
			}
		}
		else
		{
			add_token(&new_head, &new_tail, new_token(cur->type,
					strdup(cur->value)));
		}
		cur = cur->next;
	}
	return (new_head);
}