/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"
#include <ctype.h>

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
	return (val ? strdup(val) : strdup(""));
}

static char	*expand_str(const char *str, int last_status)
{
	size_t	i;
	size_t	len;
	size_t	res_len;
	char	*result;
			size_t start;
			char varname[256] = {0};
			char *val;
			size_t vlen;

	i = 0;
	len = strlen(str);
	result = calloc(1, len + 1);
	res_len = 0;
	while (i < len)
	{
		if (str[i] == '$')
		{
			i++;
			if (i < len && str[i] == '?')
			{
				i++;
				val = itoa_status(last_status);
			}
			else
			{
				start = i;
				while (i < len && (isalnum((unsigned char)str[i])
						|| str[i] == '_'))
					i++;
				if (i == start)
				{
					// No var name, keep '$'
					result = realloc(result, res_len + 2 + (len - i));
					result[res_len++] = '$';
					continue ;
				}
				strncpy(varname, str + start, i - start);
				val = get_env_value(varname);
			}
			vlen = strlen(val);
			result = realloc(result, res_len + vlen + (len - i) + 1);
			memcpy(result + res_len, val, vlen);
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

t_token	*expand(t_token *tokens, int last_status)
{
	t_token *cur;

	cur = tokens;
	while (cur)
	{
		if (cur->type == TOKEN_WORD && cur->value)
		{
			if (cur->quote == QUOTE_SINGLE)
			{
				// no expansion in single quotes
			}
			else if (strchr(cur->value, '$'))
			{
				char *expanded;

				expanded = expand_str(cur->value, last_status);
				free(cur->value);
				cur->value = expanded;
			}
		}
		cur = cur->next;
	}
	return (tokens);
}