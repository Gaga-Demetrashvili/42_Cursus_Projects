/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/22 22:19:33 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*build_full_path(const char *dir, const char *cmd)
{
	size_t	len;
	char	*full_path;
	size_t	i;
	size_t	j;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full_path = malloc(len);
	if (!full_path)
		return (NULL);
	i = 0;
	while (dir[i])
	{
		full_path[i] = dir[i];
		i++;
	}
	full_path[i++] = '/';
	j = 0;
	while (cmd[j])
		full_path[i++] = cmd[j++];
	full_path[i] = '\0';
	return (full_path);
}

static char	*find_next_dir(char *path, size_t *pos)
{
	size_t	start;
	size_t	i;
	char	*dir;

	while (path[*pos] == ':')
		(*pos)++;
	if (path[*pos] == '\0')
		return (NULL);
	start = *pos;
	while (path[*pos] && path[*pos] != ':')
		(*pos)++;
	i = 0;
	dir = malloc(*pos - start + 1);
	if (!dir)
		return (NULL);
	while (start + i < *pos)
	{
		dir[i] = path[start + i];
		i++;
	}
	dir[i] = '\0';
	return (dir);
}

static char	*search_in_path(char *path_copy, const char *cmd)
{
	char	*dir;
	char	*full_path;
	size_t	pos;

	pos = 0;
	dir = find_next_dir(path_copy, &pos);
	while (dir)
	{
		full_path = build_full_path(dir, cmd);
		free(dir);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = find_next_dir(path_copy, &pos);
	}
	free(path_copy);
	return (NULL);
}

char	*find_in_path(const char *cmd, char **envp)
{
	char	*path_env;
	char	*path_copy;
	char	*result;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_path_env(envp);
	if (!path_env)
		return (ft_strdup(cmd));
	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (ft_strdup(cmd));
	result = search_in_path(path_copy, cmd);
	if (result)
		return (result);
	return (ft_strdup(cmd));
}
