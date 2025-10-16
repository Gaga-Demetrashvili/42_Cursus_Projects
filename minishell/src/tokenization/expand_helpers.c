/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/16 00:00:00 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"
#include <stdlib.h>
#include <string.h>

char	*itoa_status(int n)
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

char	*get_env_value(const char *name)
{
	char	*val;

	val = getenv(name);
	if (val)
		return (strdup(val));
	return (strdup(""));
}

char	*append_char(char *result, char c)
{
	size_t	l;

	l = strlen(result);
	result = realloc(result, l + 2);
	result[l] = c;
	result[l + 1] = '\0';
	return (result);
}

char	*append_cstr_take(char *result, char *val)
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
