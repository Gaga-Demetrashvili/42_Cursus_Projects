#include "minishell_types.h"
#include <stdlib.h>
#include <string.h>

// Helper: count tokens for argv
static int	count_args(t_token *cur)
{
	int	count;

	count = 0;
	while (cur && cur->type == TOKEN_WORD)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

// Helper: build argv array from tokens
static char	**build_argv(t_token **cur)
{
	int		argc;
	char	**argv;
	int		i;

	argc = count_args(*cur);
	argv = malloc(sizeof(char *) * (argc + 1));
	i = 0;
	while (*cur && (*cur)->type == TOKEN_WORD)
	{
		argv[i++] = strdup((*cur)->value);
		*cur = (*cur)->next;
	}
	argv[i] = NULL;
	return (argv);
}

// Forward declarations
static t_ast	*parse_and_or(t_token **cur);
static t_ast	*parse_pipe(t_token **cur);
static t_ast	*parse_command(t_token **cur);

// Main parse entry
// Usage: t_ast *tree = parse(tokens);
t_ast	*parse(t_token *tokens)
{
	t_token	*cur;
	t_ast	*tree;

	cur = tokens;
	tree = parse_and_or(&cur);
	return (tree);
}

// Parse && and ||
static t_ast	*parse_and_or(t_token **cur)
{
	t_ast			*left;
	t_token_type	op;
	t_ast			*right;

	left = parse_pipe(cur);
	while (*cur && ((*cur)->type == TOKEN_AND || (*cur)->type == TOKEN_OR))
	{
		op = (*cur)->type;
		*cur = (*cur)->next;
		right = parse_pipe(cur);
		if (op == TOKEN_AND)
			left = create_and_node(left, right);
		else
			left = create_or_node(left, right);
	}
	return (left);
}

// Parse pipes
static t_ast	*parse_pipe(t_token **cur)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_command(cur);
	while (*cur && (*cur)->type == TOKEN_PIPE)
	{
		*cur = (*cur)->next;
		right = parse_command(cur);
		left = create_pipe_node(left, right);
	}
	return (left);
}

// Parse command, arguments, redirections, and parentheses
t_ast	*parse_command(t_token **cur)
{
	t_ast *node;
	char **argv;
	char *infile = NULL, *outfile = NULL, *heredoc;
	int append;
	t_token_type redir;

	// Handle parentheses
	if (*cur && (*cur)->type == TOKEN_LPAREN)
	{
		*cur = (*cur)->next;
		node = parse_and_or(cur);
		if (*cur && (*cur)->type == TOKEN_RPAREN)
			*cur = (*cur)->next;
		return (node);
	}
	// Collect command and arguments
	argv = build_argv(cur);
	infile = NULL, outfile = NULL, heredoc = NULL;
	append = 0;
	// Handle redirections
	while (*cur && ((*cur)->type == TOKEN_REDIR_IN
			|| (*cur)->type == TOKEN_REDIR_OUT || (*cur)->type == TOKEN_APPEND
			|| (*cur)->type == TOKEN_HEREDOC))
	{
		redir = (*cur)->type;
		*cur = (*cur)->next;
		if (*cur && (*cur)->type == TOKEN_WORD)
		{
			if (redir == TOKEN_REDIR_IN)
				infile = strdup((*cur)->value);
			else if (redir == TOKEN_REDIR_OUT)
			{
				outfile = strdup((*cur)->value);
				append = 0;
			}
			else if (redir == TOKEN_APPEND)
			{
				outfile = strdup((*cur)->value);
				append = 1;
			}
			else if (redir == TOKEN_HEREDOC)
				heredoc = strdup((*cur)->value);
			*cur = (*cur)->next;
		}
	}
	return (create_command_node(argv, infile, outfile, append, heredoc));
}