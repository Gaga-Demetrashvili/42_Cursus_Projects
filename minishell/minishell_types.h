/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:22:14 by gdemetra          #+#    #+#             */
/*   Updated: 2025/09/24 22:53:10 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gb_collect.h"
#include <stdlib.h>

typedef enum e_ast_type
{
	AST_COMMAND,
	AST_AND,
	AST_OR,
	AST_REDIR_IN,     // <
	AST_REDIR_OUT,    // >
	AST_REDIR_APPEND, // >>
	AST_HEREDOC,      // <<
	AST_PIPE
}					t_ast_type;

typedef struct s_ast
{
	t_ast_type type; // Command, AND, OR, redirection
	char **argv;     // Only used for commands

	struct s_ast	*left;
	struct s_ast	*right;

	char *infile;  // Only for commands with <
	char *outfile; // Only for commands with > or >>
	int append;    // 1 if >>, 0 if >
	char *heredoc; // Only for commands with <<
}					t_ast;

t_ast				*create_command_node(char **argv, char *infile,
						char *outfile, int append, char *heredoc);
t_ast				*create_and_node(t_ast *left, t_ast *right);
t_ast				*create_or_node(t_ast *left, t_ast *right);
t_ast				*create_redir_node(t_ast_type type, char *file_or_delim,
						t_ast *command);