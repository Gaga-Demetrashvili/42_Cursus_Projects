/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	run_command_child(t_ast *node, int heredoc_fd, int stdin_pre_set)
{
	setup_child_signals();
	setup_stdin(node, heredoc_fd, stdin_pre_set);
	setup_stdout(node);
	execvp(node->argv[0], node->argv);
	perror("execvp");
	exit(127);
}

static int	wait_for_child(pid_t pid)
{
	int	status;

	status = 0;
	if (waitpid(pid, &status, 0) < 0)
		return (1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_command(t_ast *node)
{
	int		heredoc_fd;
	pid_t	pid;

	if (!node || !node->argv || !node->argv[0])
		return (1);
	heredoc_fd = -1;
	if (node->heredoc)
		heredoc_fd = collect_heredoc(node->heredoc);
	pid = fork();
	if (pid == 0)
		run_command_child(node, heredoc_fd, 0);
	if (heredoc_fd >= 0)
		close(heredoc_fd);
	return (wait_for_child(pid));
}
