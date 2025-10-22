/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/22 22:17:59 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include <stdlib.h>
#include <unistd.h>

static int	should_keep(char *env_entry, const char *var_name, size_t name_len)
{
	return (!(ft_strncmp(env_entry, var_name, name_len) == 0
			&& env_entry[name_len] == '='));
}

static int	count_remaining(char **envp, const char *var_name, size_t name_len)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (envp[i])
	{
		if (should_keep(envp[i], var_name, name_len))
			count++;
		i++;
	}
	return (count);
}

static char	**remove_env_var(char **envp, const char *var_name)
{
	int		i;
	int		j;
	size_t	name_len;
	char	**new_envp;

	name_len = ft_strlen(var_name);
	new_envp = malloc(sizeof(char *) * (count_remaining(envp, var_name,
					name_len) + 1));
	if (!new_envp)
		return (envp);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (should_keep(envp[i], var_name, name_len))
			new_envp[j++] = envp[i];
		else
			free(envp[i]);
		i++;
	}
	new_envp[j] = NULL;
	free(envp);
	return (new_envp);
}

int	builtin_unset(char **argv, char ***envp)
{
	int	i;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		*envp = remove_env_var(*envp, argv[i]);
		i++;
	}
	return (0);
}
