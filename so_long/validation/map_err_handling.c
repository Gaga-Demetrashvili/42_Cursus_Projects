/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_err_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:22:58 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/15 20:20:27 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	not_rectangular_handler(void)
{
	ft_putstr_fd(map_err_config()->map_not_rec_err_msg, 1);
}

void	only_empty_rows_handler(void)
{
	ft_putstr_fd(map_err_config()->only_empty_rows_err_msg, 1);
}

void	not_enclosed_by_walls_handler(void)
{
	ft_putstr_fd(map_err_config()->not_enclosed_by_walls_err_msg, 1);
}

void	invalid_char_handler(void)
{
	ft_putstr_fd(map_err_config()->invalid_char_err_msg, 1);
}

void	invalid_content_handler(void)
{
	ft_putstr_fd(map_err_config()->invalid_content_err_msg, 1);
}
