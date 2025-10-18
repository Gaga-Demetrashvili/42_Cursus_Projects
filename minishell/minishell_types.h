/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:22:14 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/18 17:41:00 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
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
	int				quote;
	struct s_token	*next;
}					t_token;

typedef struct s_tokctx
{
	t_token			*head;
	t_token			*tail;
}					t_tokctx;

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	int				append;
	char			*heredoc;
}					t_cmd;

typedef struct s_ast
{
	t_token_type	type;
	t_cmd			*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

// ast node creators
t_ast				*create_command_node(t_cmd *cmd);
t_ast				*create_operator_node(t_ast *left, t_ast *right,
						t_token_type type);
t_cmd				*create_cmd(void);

// tokenization
t_token				*new_token(t_token_type type, char *value,
						t_quote_type quote);
void				token_chainer(t_tokctx *ctx, t_token_type type, char *value,
						t_quote_type quote);
int					is_operator_char(char c);
int					handle_operator_case(t_tokctx *ctx, const char *input,
						size_t *i);
int					handle_quote_case(t_tokctx *ctx, const char *input,
						size_t *i, size_t len);
t_token				*tokenize(const char *input);
void				add_token(t_token **head, t_token **tail, t_token *new_tok);
void				dup_and_add(t_token **head, t_token **tail, t_token *src);

// expansion (env vars + wildcards)
t_token				*expand(t_token *tokens, int last_status);
t_token				*expand_wildcards(t_token *tokens);

// parsing
t_ast				*parse(t_token *tokens);
void				parse_redirection(t_token **cur, t_cmd *cmd);
int					count_args(t_token *cur);
char				**build_argv(t_token **cur);
void				determine_redirection(t_token_type redir, const char *val,
						t_cmd *cmd);

// execution
int					execute(t_ast *node);

// libft functions
size_t				ft_strlen(const char *str);
char				*ft_itoa(int n);

// debugging helpers
void				print_ast(const t_ast *node, int depth);
void				print_token_lst(t_token *token);