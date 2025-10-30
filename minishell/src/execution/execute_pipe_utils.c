/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/20 21:31:17 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_types.h"
#include <unistd.h>

void	close_pipe_fds(int *pfd, int left_heredoc_fd, int right_heredoc_fd)
{
	close(pfd[0]);
	close(pfd[1]);
	if (left_heredoc_fd >= 0)
		close(left_heredoc_fd);
	if (right_heredoc_fd >= 0)
		close(right_heredoc_fd);
}
