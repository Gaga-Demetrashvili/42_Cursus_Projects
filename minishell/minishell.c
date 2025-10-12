#include "minishell_types.h"

int	main(int ac, char **av)
{
	char	*input;
	t_ast	*tree;
	t_token	*expanded_tokens;
	t_token	*globbed_tokens;
	t_token	*tokens;
	int		val;

	// while (1)
	// {
	// 	input = readline("minishell: ");
	// 	if (input)
	// 	{
	// 		add_history(input);
	// 		t_token *tokens = tokenize(input); // You need to implement this
	// 		t_ast *tree = parse(tokens);       // You need to implement this
	// 		execute(tree);                     // You need to implement this
	// 		free_ast(tree);
	// 		free_tokens(tokens);
	// 		free(input);
	// 	}
	// }
	(void)ac;
	(void)av;
	while (1)
	{
		input = readline("minishell: ");
		if (input)
		{
			add_history(input);
			tokens = tokenize(input);
			// You need to implement this
			// print_token_lst(tokens);
			// env variable expansion
			expanded_tokens = expand(tokens);
			// wildcard expansion
			globbed_tokens = expand_wildcards(expanded_tokens);
			tree = parse(globbed_tokens);
			val = execute(tree);
			// print_ast(tree, 0);
		}
	}
	return (0);
}
