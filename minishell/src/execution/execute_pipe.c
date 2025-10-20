/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/20 21:31:06 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_types.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern char	**g_envp;

static void	exec_left_child(t_ast *node, int *pfd, int left_heredoc_fd)
{
	if (dup2(pfd[1], STDOUT_FILENO) < 0)
	{
		perror("dup2 pipe write");
		exit(1);
	}
	close(pfd[0]);
	close(pfd[1]);
	if (node->left && node->left->type == TOKEN_WORD)
		run_command_child(node->left, left_heredoc_fd, 0);
	else
		exit(execute(node->left, &g_envp));
}

static void	exec_right_child(t_ast *node, int *pfd, int right_heredoc_fd)
{
	if (right_heredoc_fd < 0)
	{
		if (dup2(pfd[0], STDIN_FILENO) < 0)
		{
			perror("dup2 pipe read");
			exit(1);
		}
	}
	close(pfd[0]);
	close(pfd[1]);
	if (node->right && node->right->type == TOKEN_WORD)
		run_command_child(node->right, right_heredoc_fd, 1);
	else
		exit(execute(node->right, &g_envp));
}

static void	collect_pipe_heredocs(t_ast *node, int *left_fd, int *right_fd)
{
	*left_fd = -1;
	*right_fd = -1;
	if (node->left && node->left->type == TOKEN_WORD && node->left->cmd
		&& node->left->cmd->heredoc)
		*left_fd = collect_heredoc(node->left->cmd->heredoc);
	if (node->right && node->right->type == TOKEN_WORD && node->right->cmd
		&& node->right->cmd->heredoc)
		*right_fd = collect_heredoc(node->right->cmd->heredoc);
}

static int	wait_pipe_children(pid_t pid_left, pid_t pid_right)
{
	int	status_right;
	int	status_left;

	status_right = 0;
	status_left = 0;
	waitpid(pid_left, &status_left, 0);
	waitpid(pid_right, &status_right, 0);
	if (WIFEXITED(status_right))
		return (WEXITSTATUS(status_right));
	if (WIFSIGNALED(status_right))
		return (128 + WTERMSIG(status_right));
	return (1);
}

int	execute_pipe(t_ast *node, char ***envp)
{
	int		pfd[2];
	int		left_heredoc_fd;
	int		right_heredoc_fd;
	pid_t	pid_left;
	pid_t	pid_right;

	(void)envp;
	if (pipe(pfd) < 0)
	{
		perror("pipe");
		return (1);
	}
	collect_pipe_heredocs(node, &left_heredoc_fd, &right_heredoc_fd);
	pid_left = fork();
	if (pid_left == 0)
		exec_left_child(node, pfd, left_heredoc_fd);
	pid_right = fork();
	if (pid_right == 0)
		exec_right_child(node, pfd, right_heredoc_fd);
	close_pipe_fds(pfd, left_heredoc_fd, right_heredoc_fd);
	return (wait_pipe_children(pid_left, pid_right));
}
