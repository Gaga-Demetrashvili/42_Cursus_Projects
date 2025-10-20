/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaindur <tbaindur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:00:00 by tbaindur          #+#    #+#             */
/*   Updated: 2025/10/20 20:35:11 by tbaindur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	print_export(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		write(1, "declare -x ", 11);
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
}

int	builtin_export(char **argv, char ***envp)
{
	(void)envp;
	if (!argv[1])
	{
		print_export(*envp);
		return (0);
	}
	write(2, "export: not fully implemented\n", 30);
	return (0);
}
