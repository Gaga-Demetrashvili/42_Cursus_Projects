/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/22 22:10:05 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./src/minishell_types.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t	g_signal = 0;

static void	sigint_prompt(int sig)
{
	g_signal = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	process_input(char *input, int val, char ***envp)
{
	t_token	*tokens;
	t_token	*expanded_tokens;
	t_token	*globbed_tokens;
	t_ast	*tree;

	tokens = tokenize(input);
	expanded_tokens = expand(tokens, val, *envp);
	globbed_tokens = expand_wildcards(expanded_tokens);
	tree = parse(globbed_tokens);
	return (execute(tree, envp));
}

static void	shell_loop(char **envp)
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
		val = process_input(input, val, &envp);
		free(input);
	}
}

static char	**dup_envp(char **envp)
{
	int		count;
	int		i;
	char	**new_envp;

	count = 0;
	while (envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (i > 0)
				free(new_envp[--i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[count] = NULL;
	return (new_envp);
}

int	main(int ac, char **av, char **envp)
{
	char	**dup_env;

	(void)ac;
	(void)av;
	dup_env = dup_envp(envp);
	if (!dup_env)
		return (1);
	signal(SIGINT, sigint_prompt);
	signal(SIGQUIT, SIG_IGN);
	shell_loop(dup_env);
	return (0);
}
