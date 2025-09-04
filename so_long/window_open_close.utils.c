/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_open_close.utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:21:05 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/15 17:59:13 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map_w(char **map)
{
	return (col_counter(map[0]) * TILE_SIZE);
}

int	get_map_h(size_t rowc)
{
	return ((int)rowc * TILE_SIZE);
}

int	close_win(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_game(game);
	exit(0);
	return (0);
}

int	handle_key(int keycode, void *param)
{
	if (keycode == W_KEY)
		move_up(param);
	else if (keycode == S_KEY)
		move_down(param);
	else if (keycode == 97)
		move_left(param);
	else if (keycode == 100)
		move_right(param);
	if (keycode == ESC_KEY)
		close_win(param);
	return (0);
}
