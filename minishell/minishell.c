#include "minishell_types.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	char	*input;

	while (1)
	{
		input = readline("minishell: ");
		if (input)
		{
			add_history(input);
			t_token *tokens = tokenize(input); // You need to implement this
			t_ast *tree = parse(tokens);       // You need to implement this
			execute(tree);                     // You need to implement this
			free_ast(tree);
			free_tokens(tokens);
			free(input);
		}
	}
	return (0);
}
