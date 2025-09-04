/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_err_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:22:44 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/14 22:07:53 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

size_t	*alloc_size_t(size_t num)
{
	size_t	*alloc_num;

	alloc_num = malloc(sizeof(size_t));
	*alloc_num = num;
	return (alloc_num);
}

t_pr_err_config	*init_input_err_config(t_pr_err_config *c)
{
	static t_pr_err_config	*config;

	if (NULL == c)
		return (config);
	c->valid_fl_ext = ".ber";
	c->map_rows_max = alloc_size_t(20);
	c->pr_arg_err_msg = "Error\nProgram should take only 1 argument.\n";
	c->fl_ext_err_msg = "Error\nWrong file descriptor (should be \".ber\")\n";
	c->fl_empty_err_msg = "Error\nFile is empty\n";
	c->fl_too_larg_err_msg = "Error\nFile is too large. More than 20 lines\n";
	c->no_such_file = "Error\nopen failed: %s\n";
	config = c;
	return (config);
}

t_pr_err_config	*input_err_config(void)
{
	return (init_input_err_config(NULL));
}
