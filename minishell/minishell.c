#include "minishell_types.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

static void	sigint_prompt(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int ac, char **av)
{
	char	*input;
	t_ast	*tree;
	t_token	*expanded_tokens;
	t_token	*globbed_tokens;
	t_token	*tokens;
	int		val;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_prompt);
	signal(SIGQUIT, SIG_IGN);
	val = 0;
	while (1)
	{
		input = readline("minishell: ");
		if (!input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		tokens = tokenize(input);
		expanded_tokens = expand(tokens, val);
		globbed_tokens = expand_wildcards(expanded_tokens);
		// print_token_lst(globbed_tokens);
		// return (0);
		tree = parse(globbed_tokens);
		// val = execute(tree);
		print_ast(tree, 0);
		free(input);
		// TODO: free tokens/AST if you add free functions
	}
	return (0);
}
