/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:59:34 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/08 23:03:57 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"
#include <ctype.h>

// Helper: get env value by name
static char	*get_env_value(const char *name)
{
	char	*val;

	val = getenv(name);
	return (val ? strdup(val) : strdup(""));
}

// Helper: expand $VAR in a string
static char	*expand_str(const char *str)
{
	char	*result;
	size_t	res_len;
	size_t	start;
	char	varname[128] = {0};
	char	*val;
	size_t	vlen;

	size_t i, len;
	i = 0, len = strlen(str);
	result = calloc(1, len + 1);
	res_len = 0;
	while (i < len)
	{
		if (str[i] == '$')
		{
			i++;
			start = i;
			while (i < len && (isalnum(str[i]) || str[i] == '_'))
				i++;
			strncpy(varname, str + start, i - start);
			val = get_env_value(varname);
			vlen = strlen(val);
			result = realloc(result, res_len + vlen + len - i + 2);
			strcpy(result + res_len, val);
			res_len += vlen;
			free(val);
		}
		else
		{
			result[res_len++] = str[i++];
		}
	}
	result[res_len] = '\0';
	return (result);
}

// Main expand function
t_token	*expand(t_token *tokens)
{
	t_token *cur = tokens;
	while (cur)
	{
		if (cur->type == TOKEN_WORD)
		{
			// Check if token is not inside single quotes
			if (cur->value && strchr(cur->value, '$'))
			{
				// Simple: expand all $VAR in token value
				char *expanded = expand_str(cur->value);
				free(cur->value);
				cur->value = expanded;
			}
		}
		cur = cur->next;
	}
	return (tokens);
}