/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"

const char	*token_type_to_string(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("TOKEN_WORD");
	if (type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	if (type == TOKEN_AND)
		return ("TOKEN_AND");
	if (type == TOKEN_OR)
		return ("TOKEN_OR");
	if (type == TOKEN_REDIR_IN)
		return ("TOKEN_REDIR_IN");
	if (type == TOKEN_REDIR_OUT)
		return ("TOKEN_REDIR_OUT");
	if (type == TOKEN_APPEND)
		return ("TOKEN_APPEND");
	if (type == TOKEN_HEREDOC)
		return ("TOKEN_HEREDOC");
	if (type == TOKEN_EOF)
		return ("TOKEN_EOF");
	if (type == TOKEN_LPAREN)
		return ("TOKEN_LPAREN");
	if (type == TOKEN_RPAREN)
		return ("TOKEN_RPAREN");
	return ("UNKNOWN");
}

void	print_indent(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
}

void	print_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	printf("[ ");
	i = 0;
	while (argv[i])
	{
		printf("'%s' ", argv[i]);
		i++;
	}
	printf("]");
}
