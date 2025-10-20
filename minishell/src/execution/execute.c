/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:59:49 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/20 20:12:19 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_types.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	execute_command(t_ast *node)
{
	int		heredoc_fd;
	pid_t	pid;
	int		status;

	if (!node || !node->cmd || !node->cmd->argv || !node->cmd->argv[0])
		return (1);
	heredoc_fd = -1;
	if (node->cmd->heredoc)
		heredoc_fd = collect_heredoc(node->cmd->heredoc);
	pid = fork();
	if (pid == 0)
		run_command_child(node, heredoc_fd, 0);
	if (heredoc_fd >= 0)
		close(heredoc_fd);
	status = 0;
	if (waitpid(pid, &status, 0) < 0)
		return (1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static int	exec_token_and(t_ast *node)
{
	int	ls;

	ls = execute(node->left);
	if (ls == 0)
		return (execute(node->right));
	if (ls)
		return (1);
	return (0);
}

static int	exec_token_or(t_ast *node)
{
	int	ls;

	ls = execute(node->left);
	if (ls != 0)
		return (execute(node->right));
	return (0);
}

int	execute(t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == TOKEN_PIPE)
		return (execute_pipe(node));
	else if (node->type == TOKEN_AND)
		return (exec_token_and(node));
	else if (node->type == TOKEN_OR)
		return (exec_token_or(node));
	else if (node->type == TOKEN_WORD)
		return (execute_command(node));
	else
	{
		fprintf(stderr, "Unsupported AST node type: %d\n", node->type);
		return (1);
	}
}
