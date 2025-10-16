/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	setup_stdin_heredoc(int heredoc_fd)
{
	if (dup2(heredoc_fd, STDIN_FILENO) < 0)
	{
		perror("dup2 heredoc");
		exit(1);
	}
	close(heredoc_fd);
	return (0);
}

int	setup_stdin_infile(t_ast *node)
{
	int	fd;

	fd = open(node->infile, O_RDONLY);
	if (fd < 0)
	{
		perror("open infile");
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 infile");
		exit(1);
	}
	close(fd);
	return (0);
}

void	setup_stdin(t_ast *node, int heredoc_fd, int stdin_pre_set)
{
	if (!stdin_pre_set)
	{
		if (heredoc_fd >= 0)
			setup_stdin_heredoc(heredoc_fd);
		else if (node->infile)
			setup_stdin_infile(node);
	}
	else
	{
		if (heredoc_fd >= 0)
			setup_stdin_heredoc(heredoc_fd);
	}
}

void	setup_stdout(t_ast *node)
{
	int	fd;
	int	flags;

	if (node->outfile)
	{
		if (node->append)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		fd = open(node->outfile, flags, 0644);
		if (fd < 0)
		{
			perror("open outfile");
			exit(1);
		}
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 outfile");
			exit(1);
		}
		close(fd);
	}
}
