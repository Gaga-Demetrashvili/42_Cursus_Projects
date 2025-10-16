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

static char	*itoa_status(int n)
{
	char	buf[16];
	int		i;
	long	nb;

	i = 15;
	buf[i--] = '\0';
	nb = n;
	if (nb == 0)
		buf[i--] = '0';
	while (nb > 0 && i >= 0)
	{
		buf[i--] = '0' + (nb % 10);
		nb /= 10;
	}
	return (strdup(&buf[i + 1]));
}

static char	*get_env_value(const char *name)
{
	char	*val;

	val = getenv(name);
	if (val)
		return (strdup(val));
	return (strdup(""));
}

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

static char	*append_char(char *result, char c)
{
	size_t	l;

	l = strlen(result);
	result = realloc(result, l + 2);
	result[l] = c;
	result[l + 1] = '\0';
	return (result);
}

static char	*append_cstr_take(char *result, char *val)
{
	size_t	l;
	size_t	vlen;

	l = strlen(result);
	vlen = strlen(val);
	result = realloc(result, l + vlen + 1);
	memcpy(result + l, val, vlen);
	result[l + vlen] = '\0';
	free(val);
	return (result);
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
