/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:22:49 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/15 19:49:02 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	check_fl_ext(char *filePath)
{
	size_t		i;
	size_t		j;
	const char	*valid_fl_ext;

	i = ft_strlen(filePath) - 4;
	j = 0;
	valid_fl_ext = input_err_config()->valid_fl_ext;
	while (valid_fl_ext[j])
	{
		if (valid_fl_ext[j++] != filePath[i++])
			return (1);
	}
	if (filePath[i] != '\0')
		return (1);
	return (0);
}

static int	check_argc(int argc)
{
	return (argc != 2);
}

int	pr_start_validations(int argc, char **argv)
{
	if (check_argc(argc) || check_fl_ext(argv[1]))
	{
		if (check_argc(argc))
			ft_putstr_fd(input_err_config()->pr_arg_err_msg, 1);
		else
			ft_putstr_fd(input_err_config()->fl_ext_err_msg, 1);
		return (1);
	}
	return (0);
}
