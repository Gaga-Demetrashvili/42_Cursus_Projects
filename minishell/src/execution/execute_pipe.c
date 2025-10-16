/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static pid_t	fork_left_child(t_ast *node, int *pfd, int left_heredoc_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_left_child_pipe(pfd);
		exec_left_child(node, left_heredoc_fd);
	}
	return (pid);
}

static pid_t	fork_right_child(t_ast *node, int *pfd, int right_heredoc_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_right_child_pipe(pfd, right_heredoc_fd);
		exec_right_child(node, right_heredoc_fd);
	}
	return (pid);
}

static void	close_pipe_and_heredocs(int *pfd, int left_fd, int right_fd)
{
	close(pfd[0]);
	close(pfd[1]);
	if (left_fd >= 0)
		close(left_fd);
	if (right_fd >= 0)
		close(right_fd);
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

int	execute_pipe(t_ast *node)
{
	int		pfd[2];
	int		left_heredoc_fd;
	int		right_heredoc_fd;
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(pfd) < 0)
	{
		perror("pipe");
		return (1);
	}
	collect_pipe_heredocs(node, &left_heredoc_fd, &right_heredoc_fd);
	pid_left = fork_left_child(node, pfd, left_heredoc_fd);
	pid_right = fork_right_child(node, pfd, right_heredoc_fd);
	close_pipe_and_heredocs(pfd, left_heredoc_fd, right_heredoc_fd);
	return (wait_pipe_children(pid_left, pid_right));
}
