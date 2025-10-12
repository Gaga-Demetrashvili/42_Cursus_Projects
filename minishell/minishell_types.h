/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:22:14 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/12 21:15:30 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gb_collect.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
t_ast				*create_pipe_node(t_ast *left, t_ast *right);

t_token				*new_token(t_token_type type, char *value);

t_token				*tokenize(const char *input);
t_token				*expand(t_token *tokens);
t_ast				*parse(t_token *tokens);
t_token				*expand_wildcards(t_token *tokens);
int					execute(t_ast *node);

void				print_ast(const t_ast *node, int depth);
void				print_token_lst(t_token *token);