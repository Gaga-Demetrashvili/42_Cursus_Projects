/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/20 21:32:05 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_types.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	setup_stdin_heredoc(int heredoc_fd)
{
	if (dup2(heredoc_fd, STDIN_FILENO) < 0)
	{
		perror("dup2 heredoc");
		exit(1);
	}
	close(heredoc_fd);
}

static void	setup_stdin_infile(const char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
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
}

static void	setup_stdin(t_ast *node, int heredoc_fd)
{
	if (heredoc_fd >= 0)
		setup_stdin_heredoc(heredoc_fd);
	else if (node->cmd->infile)
		setup_stdin_infile(node->cmd->infile);
}

static void	setup_stdout(t_ast *node)
{
	int	fd;
	int	flags;

	if (node->cmd->outfile)
	{
		flags = O_WRONLY | O_CREAT;
		if (node->cmd->append)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(node->cmd->outfile, flags, 0644);
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

void	run_command_child(t_ast *node, int heredoc_fd, int stdin_pre_set)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!stdin_pre_set)
		setup_stdin(node, heredoc_fd);
	else if (heredoc_fd >= 0)
		setup_stdin_heredoc(heredoc_fd);
	setup_stdout(node);
	execvp(node->cmd->argv[0], node->cmd->argv);
	perror("execvp");
	exit(127);
}
