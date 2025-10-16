/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/16 00:00:00 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static char	*get_var_expansion(const char *str, size_t *i, int last_status)
{
	size_t	start;
	size_t	len;
	char	varname[256];
	int		j;

	len = strlen(str);
	if (*i < len && str[*i] == '?')
	{
		(*i)++;
		return (itoa_status(last_status));
	}
	start = *i;
	while (*i < len && (isalnum((unsigned char)str[*i]) || str[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (NULL);
	j = 0;
	while (j < 256 && start + j < *i)
	{
		varname[j] = str[start + j];
		j++;
	}
	varname[j] = '\0';
	return (get_env_value(varname));
}

static void	expand_handle_dollar(const char *str, size_t *i, int last_status,
		char **result)
{
	char	*val;

	(*i)++;
	val = get_var_expansion(str, i, last_status);
	if (!val)
		*result = append_char(*result, '$');
	else
		*result = append_cstr_take(*result, val);
}

static char	*expand_str(const char *str, int last_status)
{
	size_t	i;
	size_t	len;
	char	*result;

	i = 0;
	len = strlen(str);
	result = calloc(1, 1);
	while (i < len)
	{
		if (str[i] == '$')
			expand_handle_dollar(str, &i, last_status, &result);
		else
		{
			result = append_char(result, str[i]);
			i++;
		}
	}
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
