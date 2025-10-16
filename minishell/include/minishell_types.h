/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:22:14 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/14 20:37:23 by gdemetra         ###   ########.fr       */
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
						char *outfile, int append);
void				set_command_heredoc(t_ast *node, char *heredoc);
t_ast				*create_and_node(t_ast *left, t_ast *right);
t_ast				*create_or_node(t_ast *left, t_ast *right);
t_ast				*create_pipe_node(t_ast *left, t_ast *right);

t_token				*new_token(t_token_type type, char *value,
						t_quote_type quote);

t_token				*tokenize(const char *input);
int					handle_operator_case(t_tokctx *ctx, const char *input,
						size_t *i);
int					handle_parentheses_case(t_tokctx *ctx, const char *input,
						size_t *i);
int					handle_quote_case(t_tokctx *ctx, const char *input,
						size_t *i, size_t len);
t_token				*expand(t_token *tokens, int last_status);
char				*itoa_status(int n);
char				*get_env_value(const char *name);
char				*append_char(char *result, char c);
char				*append_cstr_take(char *result, char *val);
void				add_token(t_token **head, t_token **tail,
						t_token *new_tok);
int					match_star(const char *pattern, const char *s);
int					should_skip_name(const char *name, int pat_starts_dot);
t_ast				*parse(t_token *tokens);
t_ast				*parse_command(t_token **cur, t_ast *(*parse_fn)(
							t_token **));
t_ast				*handle_parentheses(t_token **cur, t_ast *(*parse_fn)(
							t_token **));
t_token				*expand_wildcards(t_token *tokens);
int					execute(t_ast *node);

char				**build_argv(t_token **cur);
void				handle_redirections(t_token **cur, char **infile,
						char **outfile, char **heredoc);
int					get_append_from_tokens(t_token *tokens);

int					collect_heredoc(const char *delimiter);
void				setup_child_signals(void);
void				setup_stdin(t_ast *node, int heredoc_fd, int stdin_pre_set);
void				setup_stdout(t_ast *node);
void				run_command_child(t_ast *node, int heredoc_fd,
						int stdin_pre_set);
int					execute_command(t_ast *node);
void				collect_pipe_heredocs(t_ast *node, int *l_fd, int *r_fd);
void				setup_left_child_pipe(int *pfd);
void				exec_left_child(t_ast *node, int left_heredoc_fd);
void				setup_right_child_pipe(int *pfd, int right_heredoc_fd);
void				exec_right_child(t_ast *node, int right_heredoc_fd);
int					execute_pipe(t_ast *node);

const char			*token_type_to_string(t_token_type type);
void				print_indent(int depth);
void				print_argv(char **argv);
void				print_ast(const t_ast *node, int depth);
void				print_token_lst(t_token *token);