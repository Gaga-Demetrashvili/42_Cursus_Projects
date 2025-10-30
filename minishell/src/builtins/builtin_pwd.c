/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
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

int	builtin_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}
