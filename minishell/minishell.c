/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	process_input(char *input, int last_val)
{
	t_token	*tokens;
	t_token	*expanded;
	t_token	*globbed;
	t_ast	*tree;

	tokens = tokenize(input);
	expanded = expand(tokens, last_val);
	globbed = expand_wildcards(expanded);
	tree = parse(globbed);
	return (execute(tree));
}

static int	handle_empty_input(char *input)
{
	if (input[0] == '\0')
	{
		free(input);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	char	*input;
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
		if (handle_empty_input(input))
			continue ;
		add_history(input);
		val = process_input(input, val);
		free(input);
	}
	return (0);
}
