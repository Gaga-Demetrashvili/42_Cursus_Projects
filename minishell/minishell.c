/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/20 21:41:06 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./src/minishell_types.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

char		**g_envp;

static void	sigint_prompt(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	process_input(char *input, int val)
{
	t_token	*tokens;
	t_token	*expanded_tokens;
	t_token	*globbed_tokens;
	t_ast	*tree;

	tokens = tokenize(input);
	expanded_tokens = expand(tokens, val);
	globbed_tokens = expand_wildcards(expanded_tokens);
	tree = parse(globbed_tokens);
	return (execute(tree, &g_envp));
}

static void	shell_loop(void)
{
	char	*input;
	int		val;

	val = 0;
	while (1)
	{
		input = readline("minishell$ ");
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
		val = process_input(input, val);
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	g_envp = envp;
	signal(SIGINT, sigint_prompt);
	signal(SIGQUIT, SIG_IGN);
	shell_loop();
	return (0);
}
