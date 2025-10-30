/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/22 22:24:58 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static int	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
			&& c <= 'Z'));
}

int	is_valid_export_id(const char *str)
{
	size_t	i;
	char	*equals;

	if (!str || !str[0])
		return (0);
	equals = ft_strchr(str, '=');
	if (equals && equals == str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && (equals == NULL || &str[i] < equals))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_sorted_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		write(1, "declare -x ", 11);
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
}
