/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/22 22:45:13 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_types.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void	write_lines_until_delimiter(int fd, const char *delim, char **envp,
		int last_status)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		expanded = expand_string(line, last_status, envp);
		if (expanded)
		{
			write(fd, expanded, ft_strlen(expanded));
			free(expanded);
		}
		write(fd, "\n", 1);
		free(line);
	}
}

int	collect_heredoc(const char *delim, char **envp, int last_status)
{
	int		pfd[2];
	pid_t	pid;
	int		status;

	if (pipe(pfd) < 0)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pfd[0]);
		write_lines_until_delimiter(pfd[1], delim, envp, last_status);
		close(pfd[1]);
		exit(0);
	}
	close(pfd[1]);
	waitpid(pid, &status, 0);
	return (pfd[0]);
}
