/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaga <gaga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:22:14 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/16 23:39:05 by gaga             ###   ########.fr       */
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

typedef enum e_quote_type
{
	QUOTE_NONE = 0,
	QUOTE_SINGLE = 1,
	QUOTE_DOUBLE = 2
}					t_quote_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int quote; // QUOTE_NONE | QUOTE_SINGLE | QUOTE_DOUBLE
	struct s_token	*next;
}					t_token;

typedef struct s_tokctx
{
	t_token			*head;
	t_token			*tail;
}					t_tokctx;

typedef struct s_ast
{
	t_token_type	type;
	char			**argv;

	struct s_ast	*left;
	struct s_ast	*right;

	char			*infile;
	char			*outfile;
	int				append;
	char			*heredoc;
}					t_ast;

t_ast				*create_command_node(char **argv, char *infile,
						char *outfile, int append, char *heredoc);
t_ast				*create_and_node(t_ast *left, t_ast *right);
t_ast				*create_or_node(t_ast *left, t_ast *right);
t_ast				*create_pipe_node(t_ast *left, t_ast *right);

t_token				*new_token(t_token_type type, char *value,
						t_quote_type quote);
void				token_chainer(t_tokctx *ctx, t_token_type type, char *value,
						t_quote_type quote);

t_token				*tokenize(const char *input);
t_token				*expand(t_token *tokens, int last_status);
t_ast				*parse(t_token *tokens);
t_token				*expand_wildcards(t_token *tokens);
int					execute(t_ast *node);

// tokenizer helpers
int					handle_operator_case(t_tokctx *ctx, const char *input,
						size_t *i);
int					handle_parentheses_case(t_tokctx *ctx, const char *input,
						size_t *i);
int					handle_quote_case(t_tokctx *ctx, const char *input,
						size_t *i, size_t len);

void				print_ast(const t_ast *node, int depth);
void				print_token_lst(t_token *token);