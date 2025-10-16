/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:43:59 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"

static t_ast	*init_command_node(void)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = TOKEN_WORD;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static void	set_cmd_redirections(t_ast *node, char *infile, char *outfile)
{
	node->infile = infile;
	node->outfile = outfile;
}

t_ast	*create_command_node(char **argv, char *infile,
			char *outfile, int append)
{
	t_ast	*node;

	node = init_command_node();
	if (!node)
		return (NULL);
	node->argv = argv;
	set_cmd_redirections(node, infile, outfile);
	node->append = append;
	node->heredoc = NULL;
	return (node);
}

void	set_command_heredoc(t_ast *node, char *heredoc)
{
	if (node)
		node->heredoc = heredoc;
}
