/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:54:52 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 16:45:00 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_types.h"
#include <ctype.h>

static char	*get_env_value(const char *name)
{
	char	*val;
	char	*res;

	val = getenv(name);
	if (val)
		res = strdup(val);
	else
		res = strdup("");
	return (res);
}

static void	append_value(char **dst, size_t *res_len, const char *val,
		size_t tail_estimate)
{
	size_t	vlen;

	if (!val)
		return ;
	vlen = strlen(val);
	*dst = realloc(*dst, *res_len + vlen + tail_estimate + 1);
	if (!*dst)
		return ;
	memcpy(*dst + *res_len, val, vlen);
	*res_len += vlen;
}

static char	*expand_dollar(const char *s, size_t *i, size_t len,
		int last_status)
{
	size_t	start;
	char	*name;

	(*i)++;
	if (*i < len && s[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(last_status));
	}
	start = *i;
	while (*i < len && (isalnum((unsigned char)s[*i]) || s[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (strdup("$"));
	name = strndup(s + start, *i - start);
	if (!name)
		return (strdup(""));
	name = get_env_value(name);
	return (name);
}

static char	*expand_str(const char *str, int last_status)
{
	size_t	i;
	size_t	len;
	size_t	res_len;
	char	*result;
	char	*val;

	i = 0;
	len = strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	res_len = 0;
	while (i < len)
	{
		if (str[i] == '$')
		{
			val = expand_dollar(str, &i, len, last_status);
			append_value(&result, &res_len, val, len - i);
			free(val);
		}
		else
			result[res_len++] = str[i++];
	}
	result[res_len] = '\0';
	return (result);
}

t_token	*expand(t_token *tokens, int last_status)
{
	t_token	*cur;
	char	*expanded;

	cur = tokens;
	while (cur)
	{
		if (cur->type == TOKEN_WORD && cur->value)
		{
			if (cur->quote != QUOTE_SINGLE && strchr(cur->value, '$'))
			{
				expanded = expand_str(cur->value, last_status);
				free(cur->value);
				cur->value = expanded;
			}
		}
		cur = cur->next;
	}
	return (tokens);
}
