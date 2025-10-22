/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:59:49 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/22 22:42:27 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_types.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	execute_command(t_ast *node, char ***envp)
{
	int		heredoc_fd;
	pid_t	pid;
	int		status;

	if (!node || !node->cmd || !node->cmd->argv || !node->cmd->argv[0])
		return (1);
	if (is_builtin(node->cmd->argv[0]) && !node->cmd->outfile
		&& !node->cmd->infile)
		return (execute_builtin(node->cmd->argv, envp));
	heredoc_fd = -1;
	if (node->cmd->heredoc)
		heredoc_fd = collect_heredoc(node->cmd->heredoc, *envp, 0);
	pid = fork();
	if (pid == 0)
		run_command_child(node, heredoc_fd, 0, *envp);
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

static int	exec_token_and(t_ast *node, char ***envp)
{
	int	ls;

	ls = execute(node->left, envp);
	if (ls == 0)
		return (execute(node->right, envp));
	if (ls)
		return (1);
	return (0);
}

static int	exec_token_or(t_ast *node, char ***envp)
{
	int	ls;

	ls = execute(node->left, envp);
	if (ls != 0)
		return (execute(node->right, envp));
	return (0);
}

int	execute(t_ast *node, char ***envp)
{
	if (!node)
		return (0);
	if (node->type == TOKEN_PIPE)
		return (execute_pipe(node, envp));
	else if (node->type == TOKEN_AND)
		return (exec_token_and(node, envp));
	else if (node->type == TOKEN_OR)
		return (exec_token_or(node, envp));
	else if (node->type == TOKEN_WORD)
		return (execute_command(node, envp));
	else
	{
		write(2, "Unsupported AST node type\n", 26);
		return (1);
	}
}
