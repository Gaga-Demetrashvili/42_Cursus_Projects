/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/20 20:13:31 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_types.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	write_lines_until_delimiter(int fd, const char *delimiter)
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
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
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
	write_lines_until_delimiter(wfd, delimiter);
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
