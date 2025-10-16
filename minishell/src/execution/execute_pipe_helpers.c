/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_helpers.c                             :+:      :+:    :+:   */
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
#include <unistd.h>

void	collect_pipe_heredocs(t_ast *node, int *left_fd, int *right_fd)
{
	*left_fd = -1;
	*right_fd = -1;
	if (node->left && node->left->type == TOKEN_WORD
		&& node->left->heredoc)
		*left_fd = collect_heredoc(node->left->heredoc);
	if (node->right && node->right->type == TOKEN_WORD
		&& node->right->heredoc)
		*right_fd = collect_heredoc(node->right->heredoc);
}

void	setup_left_child_pipe(int *pfd)
{
	if (dup2(pfd[1], STDOUT_FILENO) < 0)
	{
		perror("dup2 pipe write");
		exit(1);
	}
	close(pfd[0]);
	close(pfd[1]);
}

void	exec_left_child(t_ast *node, int left_heredoc_fd)
{
	if (node->left && node->left->type == TOKEN_WORD)
		run_command_child(node->left, left_heredoc_fd, 0);
	else
		exit(execute(node->left));
}

void	setup_right_child_pipe(int *pfd, int right_heredoc_fd)
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
}

void	exec_right_child(t_ast *node, int right_heredoc_fd)
{
	if (node->right && node->right->type == TOKEN_WORD)
		run_command_child(node->right, right_heredoc_fd, 1);
	else
		exit(execute(node->right));
}
