/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:22:14 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/05 20:25:36 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gb_collect.h"
#include <stdlib.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,      // |
	TOKEN_AND,       // &&
	TOKEN_OR,        // ||
	TOKEN_REDIR_IN,  // <
	TOKEN_REDIR_OUT, // >
	TOKEN_APPEND,    // >>
	TOKEN_HEREDOC,   // <<
	TOKEN_EOF,
	TOKEN_LPAREN, // (
	TOKEN_RPAREN, // )
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_ast
{
	t_token_type type; // Command, AND, OR, redirection
	char **argv;       // Only used for commands

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
t_ast				*create_redir_node(t_token_type type, char *file_or_delim,
						t_token_type *command);