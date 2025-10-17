/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:52:45 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 17:04:20 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"

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
	if (!argv)
		return ;
	printf("[ ");
	for (int i = 0; argv[i]; i++)
	{
		printf("'%s' ", argv[i]);
	}
	printf("]");
}

void	print_token_lst(t_token *token)
{
	if (!token)
		printf("Linked list head is null!\n");
	while (token)
	{
		printf("%s - \"%s\" (%d)\n", token_type_to_string(token->type),
			token->value, (int)token->quote);
		token = token->next;
	}
}

void	print_ast(const t_ast *node, int depth)
{
	if (!node)
		return ;
	for (int i = 0; i < depth; i++)
		printf("  ");
	printf("%s", token_type_to_string(node->type));
	if (node->type == TOKEN_WORD)
	{
		printf(" ");
		print_argv(node->argv);
		if (node->infile)
			printf(" < '%s'", node->infile);
		if (node->outfile)
			printf(" > '%s'%s", node->outfile, node->append ? " (append)" : "");
		if (node->heredoc)
			printf(" << '%s'", node->heredoc);
	}
	printf("\n");
	if (node->left)
		print_ast(node->left, depth + 1);
	if (node->right)
		print_ast(node->right, depth + 1);
}
