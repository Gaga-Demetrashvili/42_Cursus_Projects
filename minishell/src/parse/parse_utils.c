/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:38:15 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/22 22:09:29 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	parse_redirection(t_token **cur, t_cmd *cmd)
{
	t_token_type	redir;

	while (*cur && ((*cur)->type == TOKEN_REDIR_IN
			|| (*cur)->type == TOKEN_REDIR_OUT || (*cur)->type == TOKEN_APPEND
			|| (*cur)->type == TOKEN_HEREDOC))
	{
		redir = (*cur)->type;
		*cur = (*cur)->next;
		if (!*cur || (*cur)->type != TOKEN_WORD)
			break ;
		determine_redirection(redir, (*cur)->value, cmd);
		*cur = (*cur)->next;
	}
}

int	count_args(t_token *cur)
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
		argv[i++] = ft_strdup((*cur)->value);
		*cur = (*cur)->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	determine_redirection(t_token_type redir, const char *val, t_cmd *cmd)
{
	if (!val)
		return ;
	if (redir == TOKEN_REDIR_IN)
	{
		free(cmd->infile);
		cmd->infile = ft_strdup(val);
	}
	else if (redir == TOKEN_REDIR_OUT)
	{
		free(cmd->outfile);
		cmd->outfile = ft_strdup(val);
		cmd->append = 0;
	}
	else if (redir == TOKEN_APPEND)
	{
		free(cmd->outfile);
		cmd->outfile = ft_strdup(val);
		cmd->append = 1;
	}
	else if (redir == TOKEN_HEREDOC)
	{
		free(cmd->heredoc);
		cmd->heredoc = ft_strdup(val);
	}
}
