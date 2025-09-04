/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:19:00 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/15 19:48:38 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	*create_image(void *mlx, char *img_name)
{
	int	tile_size;

	tile_size = TILE_SIZE;
	return (mlx_xpm_file_to_image(mlx, img_name, &tile_size, &tile_size));
}

t_game	*init_game(void *mlx, void *win, char **map)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = mlx;
	game->win = win;
	game->map = map;
	game->wall = create_image(mlx, "assets/wall.xpm");
	game->space = create_image(mlx, "assets/space.xpm");
	game->player = create_image(mlx, "assets/player.xpm");
	game->coin = create_image(mlx, "assets/coin.xpm");
	game->exit = create_image(mlx, "assets/exit.xpm");
	game->position = find_position(map, 'P');
	game->moves = 0;
	game->is_over = 0;
	return (game);
}

int	is_coin_left(t_game *game)
{
	int	coin_c;
	int	x;
	int	y;

	coin_c = 0;
	x = 0;
	y = 0;
	while (game->map[y])
	{
		while (game->map[y][x] && game->map[y][x] != '\n')
		{
			if (game->map[y][x] == 'C')
				coin_c++;
			x++;
		}
		x = 0;
		y++;
	}
	return (coin_c);
}
