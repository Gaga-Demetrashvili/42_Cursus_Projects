/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:40:59 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/18 21:05:35 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_image(t_game *game, int x, int y)
{
	char	symbol;

	symbol = game->map[y][x];
	if (symbol == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->wall, x * TILE_SIZE,
			y * TILE_SIZE);
	if (symbol == '0')
		mlx_put_image_to_window(game->mlx, game->win, game->space, x
			* TILE_SIZE, y * TILE_SIZE);
	if (symbol == 'P')
		mlx_put_image_to_window(game->mlx, game->win, game->player, x
			* TILE_SIZE, y * TILE_SIZE);
	if (symbol == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->coin, x * TILE_SIZE,
			y * TILE_SIZE);
	if (symbol == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->exit, x * TILE_SIZE,
			y * TILE_SIZE);
}

int	draw_game(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (game->is_over)
		return (close_win(game));
	while (game->map[y])
	{
		while (game->map[y][x] && game->map[y][x] != '\n')
		{
			draw_image(game, x, y);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int	launch_game(char **map, size_t rowc)
{
	void	*mlx;
	void	*win;
	t_game	*game;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, get_map_w(map), get_map_h(rowc), "so_long");
	if (!win)
		return (1);
	game = init_game(mlx, win, map);
	if (NULL == game)
		return (1);
	mlx_hook(win, 17, 0, close_win, game);
	mlx_key_hook(win, handle_key, game);
	draw_game(game);
	mlx_loop(mlx);
	return (0);
}
