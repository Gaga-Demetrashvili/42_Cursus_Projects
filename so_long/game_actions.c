/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:24:23 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/15 19:05:34 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	shared_logic(t_game *game, char target_char, int new_x, int new_y)
{
	if (target_char == '1')
		return ;
	if (target_char == 'E')
	{
		if (is_coin_left(game))
			return ;
		else
			game->is_over = 1;
	}
	game->moves++;
	ft_printf("%d\n", game->moves);
	game->position->x = new_x;
	game->position->y = new_y;
	draw_game(game);
}

void	move_up(t_game *game)
{
	t_point	*p;
	char	target_char;

	p = game->position;
	target_char = game->map[p->y - 1][p->x];
	if (target_char == '0' || target_char == 'C')
	{
		game->map[p->y][p->x] = '0';
		game->map[p->y - 1][p->x] = 'P';
	}
	shared_logic(game, target_char, game->position->x, game->position->y - 1);
}

void	move_down(t_game *game)
{
	t_point	*p;
	char	target_char;

	p = game->position;
	target_char = game->map[p->y + 1][p->x];
	if (target_char == '0' || target_char == 'C')
	{
		game->map[p->y][p->x] = '0';
		game->map[p->y + 1][p->x] = 'P';
	}
	shared_logic(game, target_char, game->position->x, game->position->y + 1);
}

void	move_left(t_game *game)
{
	t_point	*p;
	char	target_char;

	p = game->position;
	target_char = game->map[p->y][p->x - 1];
	if (target_char == '0' || target_char == 'C')
	{
		game->map[p->y][p->x] = '0';
		game->map[p->y][p->x - 1] = 'P';
	}
	shared_logic(game, target_char, game->position->x - 1, game->position->y);
}

void	move_right(t_game *game)
{
	t_point	*p;
	char	target_char;

	p = game->position;
	target_char = game->map[p->y][p->x + 1];
	if (target_char == '0' || target_char == 'C')
	{
		game->map[p->y][p->x] = '0';
		game->map[p->y][p->x + 1] = 'P';
	}
	shared_logic(game, target_char, game->position->x + 1, game->position->y);
}
