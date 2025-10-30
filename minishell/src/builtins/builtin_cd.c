/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
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
#include <unistd.h>

int	builtin_cd(char **argv)
{
	char	*path;

	if (!argv[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			write(2, "cd: HOME not set\n", 17);
			return (1);
		}
	}
	else
		path = argv[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
