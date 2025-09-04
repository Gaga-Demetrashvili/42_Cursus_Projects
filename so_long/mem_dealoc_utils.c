/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_dealoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:23:17 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/15 17:33:06 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_str_arr(char **str_arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

void	free_str_arr_to_end(char **str_arr)
{
	size_t	i;

	i = 0;
	while (str_arr[i])
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

void	free_input_err_config(void)
{
	t_pr_err_config	*conf;

	conf = input_err_config();
	if (NULL == conf)
		return ;
	free(conf->map_rows_max);
	free(conf);
}

void	free_configs(void)
{
	free_input_err_config();
	free(map_err_config());
}

void	free_game(t_game *game)
{
	mlx_destroy_image(game->mlx, game->wall);
	mlx_destroy_image(game->mlx, game->space);
	mlx_destroy_image(game->mlx, game->player);
	mlx_destroy_image(game->mlx, game->coin);
	mlx_destroy_image(game->mlx, game->exit);
	free_str_arr_to_end(game->map);
	free(game->position);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	free_configs();
}
