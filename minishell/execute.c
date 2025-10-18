/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:59:49 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 20:21:34 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell_types.h"
// #include <fcntl.h>
// #include <readline/readline.h>
// #include <signal.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/wait.h>
// #include <unistd.h>

// // Create a unique temp file, write heredoc lines, reopen for reading,
// unlink it
// static int	collect_heredoc(const char *delimiter)
// {
// 	char	tmpl[] = "/tmp/minishell_heredoc.XXXXXX";
// 	int		wfd;
// 	char	*line;
// 	int		rfd;

// 	wfd = mkstemp(tmpl);
// 	if (wfd < 0)
// 	{
// 		perror("mkstemp");
// 		return (-1);
// 	}
// 	// Write lines until delimiter
// 	for (;;)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ; // EOF/Ctrl-D
// 		if (strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(wfd, line, strlen(line));
// 		write(wfd, "\n", 1);
// 		free(line);
// 	}
// 	// Reopen read end and unlink path
// 	rfd = open(tmpl, O_RDONLY);
// 	if (rfd < 0)
// 	{
// 		perror("open heredoc");
// 		close(wfd);
// 		unlink(tmpl);
// 		return (-1);
// 	}
// 	unlink(tmpl);
// 	close(wfd);
// 	return (rfd);
// }

// // Execute a single command node in the child.
// // If stdin_pre_set is non-zero, do not touch stdin (pipe already set).
// // If heredoc_fd >= 0 and stdin_pre_set == 0, use it as stdin.
// static void	run_command_child(t_ast *node, int heredoc_fd,
// int stdin_pre_set)
// {
// 	int	fd;
// 	int	flags;

// 	// Children: default signals so Ctrl+C/Ctrl+\ affect them
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// 	// STDIN setup
// 	if (!stdin_pre_set)
// 	{
// 		if (heredoc_fd >= 0)
// 		{
// 			if (dup2(heredoc_fd, STDIN_FILENO) < 0)
// 			{
// 				perror("dup2 heredoc");
// 				exit(1);
// 			}
// 			close(heredoc_fd);
// 		}
// 		else if (node->infile)
// 		{
// 			fd = open(node->infile, O_RDONLY);
// 			if (fd < 0)
// 			{
// 				perror("open infile");
// 				exit(1);
// 			}
// 			if (dup2(fd, STDIN_FILENO) < 0)
// 			{
// 				perror("dup2 infile");
// 				exit(1);
// 			}
// 			close(fd);
// 		}
// 	}
// 	else
// 	{
// 		// stdin already set (e.g.,
// 		// by pipe). If heredoc exists on the right side of a pipe,
// 		// we prefer heredoc over the pipe (shell behavior for input redir).
// 		if (heredoc_fd >= 0)
// 		{
// 			if (dup2(heredoc_fd, STDIN_FILENO) < 0)
// 			{
// 				perror("dup2 heredoc");
// 				exit(1);
// 			}
// 			close(heredoc_fd);
// 		}
// 	}
// 	// STDOUT setup
// 	if (node->outfile)
// 	{
// 		flags = O_WRONLY | O_CREAT | (node->append ? O_APPEND : O_TRUNC);
// 		fd = open(node->outfile, flags, 0644);
// 		if (fd < 0)
// 		{
// 			perror("open outfile");
// 			exit(1);
// 		}
// 		if (dup2(fd, STDOUT_FILENO) < 0)
// 		{
// 			perror("dup2 outfile");
// 			exit(1);
// 		}
// 		close(fd);
// 	}
// 	// Exec
// 	execvp(node->argv[0], node->argv);
// 	perror("execvp");
// 	exit(127);
// }

// // Execute a command (non-pipeline) node
// static int	execute_command(t_ast *node)
// {
// 	int		heredoc_fd;
// 	pid_t	pid;
// 	int		status;

// 	if (!node || !node->argv || !node->argv[0])
// 		return (1);
// 	// Collect heredoc in parent so user sees input
// 	heredoc_fd = -1;
// 	if (node->heredoc)
// 		heredoc_fd = collect_heredoc(node->heredoc);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		run_command_child(node, heredoc_fd, 0);
// 	}
// 	if (heredoc_fd >= 0)
// 		close(heredoc_fd);
// 	status = 0;
// 	if (waitpid(pid, &status, 0) < 0)
// 		return (1);
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	if (WIFSIGNALED(status))
// 		return (128 + WTERMSIG(status));
// 	return (1);
// }

// // Execute a pipeline: left | right
// static int	execute_pipe(t_ast *node)
// {
// 	int		pfd[2];
// 	int		left_heredoc_fd;
// 	int		right_heredoc_fd;
// 	pid_t	pid_left;
// 	pid_t	pid_right;
// 	int		status_right;
// 	int		status_left;

// 	if (pipe(pfd) < 0)
// 	{
// 		perror("pipe");
// 		return (1);
// 	}
// 	// Pre-collect heredoc for immediate command nodes so typing is visible
// 	left_heredoc_fd = -1;
// 	right_heredoc_fd = -1;
// 	if (node->left && node->left->type == TOKEN_WORD && node->left->heredoc)
// 		left_heredoc_fd = collect_heredoc(node->left->heredoc);
// 	if (node->right && node->right->type == TOKEN_WORD && node->right->heredoc)
// 		right_heredoc_fd = collect_heredoc(node->right->heredoc);
// 	pid_left = fork();
// 	if (pid_left == 0)
// 	{
// 		// Left child: stdout -> pipe write
// 		if (dup2(pfd[1], STDOUT_FILENO) < 0)
// 		{
// 			perror("dup2 pipe write");
// 			exit(1);
// 		}
// 		close(pfd[0]);
// 		close(pfd[1]);
// 		// If left is a simple command,
// 		// run directly to avoid collecting heredoc in child
// 		if (node->left && node->left->type == TOKEN_WORD)
// 		{
// 			run_command_child(node->left, left_heredoc_fd, 0);
// 		}
// 		else
// 		{
// 			// Complex left subtree: execute recursively (may collect heredoc in child)
// 			exit(execute(node->left));
// 		}
// 	}
// 	pid_right = fork();
// 	if (pid_right == 0)
// 	{
// 		// Right child: stdin <- pipe read (unless overridden by heredoc)
// 		if (right_heredoc_fd < 0)
// 		{
// 			if (dup2(pfd[0], STDIN_FILENO) < 0)
// 			{
// 				perror("dup2 pipe read");
// 				exit(1);
// 			}
// 		}
// 		close(pfd[0]);
// 		close(pfd[1]);
// 		if (node->right && node->right->type == TOKEN_WORD)
// 		{
// 			// If heredoc exists on right, it overrides pipe stdin
// 			run_command_child(node->right, right_heredoc_fd, 1);
// 		}
// 		else
// 		{
// 			exit(execute(node->right));
// 		}
// 	}
// 	// Parent
// 	close(pfd[0]);
// 	close(pfd[1]);
// 	if (left_heredoc_fd >= 0)
// 		close(left_heredoc_fd);
// 	if (right_heredoc_fd >= 0)
// 		close(right_heredoc_fd);
// 	status_right = 0;
// 	status_left = 0;
// 	waitpid(pid_left, &status_left, 0);
// 	waitpid(pid_right, &status_right, 0);
// 	if (WIFEXITED(status_right))
// 		return (WEXITSTATUS(status_right));
// 	if (WIFSIGNALED(status_right))
// 		return (128 + WTERMSIG(status_right));
// 	return (1);
// }

// int	execute(t_ast *node)
// {
// 	if (!node)
// 		return (0);

// 	switch (node->type)
// 	{
// 	case TOKEN_PIPE:
// 		return (execute_pipe(node));
// 	case TOKEN_AND:
// 	{
// 		int ls = execute(node->left);
// 		if (ls == 0)
// 			return (execute(node->right));
// 		return (ls ? 1 : 0);
// 	}
// 	case TOKEN_OR:
// 	{
// 		int ls = execute(node->left);
// 		if (ls != 0)
// 			return (execute(node->right));
// 		return (0);
// 	}
// 	case TOKEN_WORD:
// 		return (execute_command(node));
// 	default:
// 		fprintf(stderr, "Unsupported AST node type: %d\n", node->type);
// 		return (1);
// 	}
// }