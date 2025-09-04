/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_err_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:22:41 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/15 20:23:18 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	file_is_empty_handler(char ***map_str)
{
	ft_printf(input_err_config()->fl_empty_err_msg);
	free(*map_str);
	*map_str = NULL;
}

void	file_is_too_large_handler(char ***map_str, size_t size, char *line)
{
	free(line);
	ft_printf(input_err_config()->fl_too_larg_err_msg);
	free_str_arr(*map_str, size);
	*map_str = NULL;
}

void	no_such_file_handler(void)
{
	ft_printf(input_err_config()->no_such_file, strerror(errno));
}

void	invalid_path(void)
{
	ft_printf(map_err_config()->invalid_path_err_msg);
}

void	map_too_wide_handler(void)
{
	ft_printf(map_err_config()->map_too_wide_err_msg);
}
