/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/22 22:23:44 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int			is_valid_export_id(const char *str);
void		print_sorted_env(char **envp);

static char	**update_existing(char **envp, const char *var_value, size_t nlen)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_value, nlen) == 0 && envp[i][nlen] == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup(var_value);
			return (envp);
		}
		i++;
	}
	return (NULL);
}

static char	**add_or_update_env(char **envp, const char *var_value)
{
	int		i;
	int		count;
	char	**new_envp;
	char	**updated;
	char	*equals;

	equals = ft_strchr(var_value, '=');
	if (!equals)
		return (envp);
	updated = update_existing(envp, var_value, equals - var_value);
	if (updated)
		return (updated);
	count = 0;
	while (envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return (envp);
	i = -1;
	while (++i < count)
		new_envp[i] = envp[i];
	new_envp[count] = ft_strdup(var_value);
	new_envp[count + 1] = NULL;
	free(envp);
	return (new_envp);
}

static void	export_error(char *arg)
{
	write(2, "export: not a valid identifier: ", 33);
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}

int	builtin_export(char **argv, char ***envp)
{
	int	i;

	if (!argv[1])
	{
		print_sorted_env(*envp);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (!is_valid_export_id(argv[i]))
			export_error(argv[i]);
		else
			*envp = add_or_update_env(*envp, argv[i]);
		i++;
	}
	return (0);
}
