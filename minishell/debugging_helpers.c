/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:52:45 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/18 17:32:41 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char	*token_type_to_string(t_token_type type)
{
	switch (type)
	{
	case TOKEN_WORD:
		return ("TOKEN_WORD");
	case TOKEN_PIPE:
		return ("TOKEN_PIPE");
	case TOKEN_AND:
		return ("TOKEN_AND");
	case TOKEN_OR:
		return ("TOKEN_OR");
	case TOKEN_REDIR_IN:
		return ("TOKEN_REDIR_IN");
	case TOKEN_REDIR_OUT:
		return ("TOKEN_REDIR_OUT");
	case TOKEN_APPEND:
		return ("TOKEN_APPEND");
	case TOKEN_HEREDOC:
		return ("TOKEN_HEREDOC");
	case TOKEN_EOF:
		return ("TOKEN_EOF");
	case TOKEN_LPAREN:
		return ("TOKEN_LPAREN");
	case TOKEN_RPAREN:
		return ("TOKEN_RPAREN");
	default:
		return ("UNKNOWN");
	}
}

static void	print_argv(char **argv)
{
	int	i;

	if (!argv)
	{
		printf("[]");
		return ;
	}
	printf("[");
	for (i = 0; argv[i]; i++)
	{
		if (i)
			printf(", ");
		printf("'%s'", argv[i]);
	}
	printf("]");
}

void	print_token_lst(t_token *token)
{
	if (!token)
	{
		printf("Linked list head is null!\n");
		return ;
	}
	while (token)
	{
		printf("%s - \"%s\" (%d)\n", token_type_to_string(token->type),
			token->value ? token->value : "(null)", (int)token->quote);
		token = token->next;
	}
}

void	print_ast(const t_ast *node, int depth)
{
	int	i;

	if (!node)
		return ;
	for (i = 0; i < depth; i++)
		printf("  ");
	/* prefer printing CMD for nodes that carry a t_cmd */
	if (node->cmd)
		printf("CMD");
	else
		printf("%s", token_type_to_string(node->type));
	if (node->cmd)
	{
		printf(" ");
		print_argv(node->cmd->argv);
		if (node->cmd->infile)
			printf(" < '%s'", node->cmd->infile);
		if (node->cmd->outfile)
			printf(" > '%s'%s", node->cmd->outfile,
				node->cmd->append ? " (append)" : "");
		if (node->cmd->heredoc)
			printf(" << '%s'", node->cmd->heredoc);
	}
	printf("\n");
	if (node->left)
		print_ast(node->left, depth + 1);
	if (node->right)
		print_ast(node->right, depth + 1);
}
