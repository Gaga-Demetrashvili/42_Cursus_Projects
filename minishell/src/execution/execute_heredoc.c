/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by gdemetra          #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_types.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	write_heredoc_lines(int wfd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(wfd, line, strlen(line));
		write(wfd, "\n", 1);
		free(line);
	}
	return (0);
}

static int	open_heredoc_read(const char *tmpl, int wfd)
{
	int	rfd;

	rfd = open(tmpl, O_RDONLY);
	if (rfd < 0)
	{
		perror("open heredoc");
		close(wfd);
		unlink(tmpl);
		return (-1);
	}
	unlink(tmpl);
	close(wfd);
	return (rfd);
}

int	collect_heredoc(const char *delimiter)
{
	char	tmpl[32];
	int		wfd;
	int		rfd;

	strcpy(tmpl, "/tmp/minishell_heredoc.XXXXXX");
	wfd = mkstemp(tmpl);
	if (wfd < 0)
	{
		perror("mkstemp");
		return (-1);
	}
	write_heredoc_lines(wfd, delimiter);
	rfd = open_heredoc_read(tmpl, wfd);
	return (rfd);
}
