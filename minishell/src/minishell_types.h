/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:22:14 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/22 22:26:26 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPES_H
# define MINISHELL_TYPES_H

# include <sys/types.h>

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

typedef struct s_expand_ctx
{
	const char		*str;
	size_t			len;
	char			**envp;
	int				last_status;
}					t_expand_ctx;

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
t_token				*expand(t_token *tokens, int last_status, char **envp);
t_token				*expand_wildcards(t_token *tokens);

// parsing
t_ast				*parse(t_token *tokens);
void				parse_redirection(t_token **cur, t_cmd *cmd);
int					count_args(t_token *cur);
char				**build_argv(t_token **cur);
void				determine_redirection(t_token_type redir, const char *val,
						t_cmd *cmd);

// execution
int					execute(t_ast *node, char ***envp);
int					execute_command(t_ast *node, char ***envp);
int					execute_pipe(t_ast *node, char ***envp);
void				run_command_child(t_ast *node, int heredoc_fd,
						int stdin_pre_set, char **envp);
char				*find_in_path(const char *cmd, char **envp);
int					collect_heredoc(const char *delimiter);
void				write_lines_until_delimiter(int fd, const char *delimiter);
void				close_pipe_fds(int *pfd, int left_heredoc_fd,
						int right_heredoc_fd);

// built-in commands
int					is_builtin(const char *cmd);
int					execute_builtin(char **argv, char ***envp);
int					builtin_echo(char **argv);
int					builtin_cd(char **argv);
int					builtin_pwd(void);
int					builtin_export(char **argv, char ***envp);
int					builtin_unset(char **argv, char ***envp);
int					builtin_env(char **envp);
int					builtin_exit(char **argv);

// libft functions
size_t				ft_strlen(const char *str);
char				*ft_itoa(int n);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strchr(const char *s, int c);

// debugging helpers
void				print_ast(const t_ast *node, int depth);
void				print_token_lst(t_token *token);

#endif