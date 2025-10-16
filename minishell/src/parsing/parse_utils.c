/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"

static int	count_args(t_token *cur)
{
	int	count;

	count = 0;
	while (cur && cur->type == TOKEN_WORD)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

char	**build_argv(t_token **cur)
{
	int		argc;
	char	**argv;
	int		i;

	argc = count_args(*cur);
	argv = malloc(sizeof(char *) * (argc + 1));
	i = 0;
	while (*cur && (*cur)->type == TOKEN_WORD)
	{
		argv[i++] = strdup((*cur)->value);
		*cur = (*cur)->next;
	}
	argv[i] = NULL;
	return (argv);
}
