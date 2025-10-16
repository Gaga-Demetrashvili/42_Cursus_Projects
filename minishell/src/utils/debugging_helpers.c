/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:52:45 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/08 20:56:26 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"

void	print_token_lst(t_token *token)
{
	if (!token)
		printf("Linked list head is null!\n");
	while (token)
	{
		printf("%s - %s\n", token_type_to_string(token->type), token->value);
		token = token->next;
	}
}

static void	print_word_details(const t_ast *node)
{
	const char	*append_str;

	if (node->type != TOKEN_WORD)
		return ;
	printf(" ");
	print_argv(node->argv);
	if (node->infile)
		printf(" < '%s'", node->infile);
	if (node->outfile)
	{
		if (node->append)
			append_str = " (append)";
		else
			append_str = "";
		printf(" > '%s'%s", node->outfile, append_str);
	}
	if (node->heredoc)
		printf(" << '%s'", node->heredoc);
}

void	print_ast(const t_ast *node, int depth)
{
	if (!node)
		return ;
	print_indent(depth);
	printf("%s", token_type_to_string(node->type));
	print_word_details(node);
	printf("\n");
	if (node->left)
		print_ast(node->left, depth + 1);
	if (node->right)
		print_ast(node->right, depth + 1);
}
