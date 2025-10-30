/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:54:52 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/22 22:54:48 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int			ft_isalnum_exp(int c);
char		*get_env_val(const char *name, char **envp);
void		mem_copy(void *dst, const void *src, size_t n);

static void	append_value(char **dst, size_t *res_len, const char *val,
		size_t tail_estimate)
{
	size_t	vlen;
	char	*new_dst;

	if (!val)
		return ;
	vlen = ft_strlen(val);
	new_dst = malloc(*res_len + vlen + tail_estimate + 1);
	if (!new_dst)
	{
		free(*dst);
		*dst = NULL;
		return ;
	}
	if (*dst)
	{
		mem_copy(new_dst, *dst, *res_len);
		free(*dst);
	}
	mem_copy(new_dst + *res_len, val, vlen);
	*res_len += vlen;
	*dst = new_dst;
}

static char	*expand_dollar_ctx(t_expand_ctx *ctx, size_t *i)
{
	size_t	start;
	char	*name;
	char	*value;

	(*i)++;
	if (*i < ctx->len && ctx->str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(ctx->last_status));
	}
	if (*i >= ctx->len || (!ft_isalnum_exp(ctx->str[*i])
			&& ctx->str[*i] != '_'))
		return (ft_strdup("$"));
	start = *i;
	while (*i < ctx->len && (ft_isalnum_exp(ctx->str[*i])
			|| ctx->str[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (ft_strdup(""));
	name = ft_strndup(ctx->str + start, *i - start);
	if (!name)
		return (ft_strdup(""));
	value = get_env_val(name, ctx->envp);
	free(name);
	return (value);
}

static void	process_expansion(t_expand_ctx *ctx, size_t *i, char **result,
		size_t *res_len)
{
	char	*val;

	if (ctx->str[*i] == '$')
	{
		val = expand_dollar_ctx(ctx, i);
		append_value(result, res_len, val, ctx->len - *i);
		free(val);
	}
	else
		(*result)[(*res_len)++] = ctx->str[(*i)++];
}

char	*expand_string(const char *str, int last_status, char **envp)
{
	size_t			i;
	size_t			res_len;
	char			*result;
	t_expand_ctx	ctx;

	ctx.str = str;
	ctx.len = ft_strlen(str);
	ctx.envp = envp;
	ctx.last_status = last_status;
	i = 0;
	result = malloc(ctx.len + 1);
	if (!result)
		return (NULL);
	res_len = 0;
	while (i < ctx.len)
		process_expansion(&ctx, &i, &result, &res_len);
	result[res_len] = '\0';
	return (result);
}

t_token	*expand(t_token *tokens, int last_status, char **envp)
{
	t_token	*cur;
	char	*expanded;

	cur = tokens;
	while (cur)
	{
		if (cur->type == TOKEN_WORD && cur->value)
		{
			if (cur->quote != QUOTE_SINGLE && ft_strchr(cur->value, '$'))
			{
				expanded = expand_string(cur->value, last_status, envp);
				free(cur->value);
				cur->value = expanded;
			}
		}
		cur = cur->next;
	}
	return (tokens);
}
