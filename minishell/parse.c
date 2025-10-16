#include "minishell_types.h"

static t_ast	*parse_and_or(t_token **cur);
static t_ast	*parse_pipe(t_token **cur);

t_ast	*parse(t_token *tokens)
{
	t_token	*cur;
	t_ast	*tree;

	cur = tokens;
	tree = parse_and_or(&cur);
	return (tree);
}

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

static t_ast	*handle_parentheses(t_token **cur)
{
	t_ast	*node;

	*cur = (*cur)->next;
	node = parse_and_or(cur);
	if (*cur && (*cur)->type == TOKEN_RPAREN)
		*cur = (*cur)->next;
	return (node);
}

static t_ast	*build_cmd_node(char **argv, t_token **cur)
{
	char	*infile;
	char	*outfile;
	char	*heredoc;
	int		append;

	infile = NULL;
	outfile = NULL;
	heredoc = NULL;
	append = get_append_from_tokens(*cur);
	handle_redirections(cur, &infile, &outfile, &heredoc);
	return (create_command_node(argv, infile, outfile, append, heredoc));
}

t_ast	*parse_command(t_token **cur)
{
	char	**argv;

	if (*cur && (*cur)->type == TOKEN_LPAREN)
		return (handle_parentheses(cur));
	argv = build_argv(cur);
	return (build_cmd_node(argv, cur));
}
