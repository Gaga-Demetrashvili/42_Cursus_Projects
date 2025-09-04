/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:23:14 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/14 19:24:07 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	map_validations(char **map, size_t i)
{
	if (consists_of_invalid_chars(map[i]) || is_not_rectangular(map[i], i)
		|| is_not_enclosed_by_walls(map[i], i, col_counter(map[i]),
			NULL == map[i + 1]) || consists_of_invalid_content(map[i],
			NULL == map[i + 1]))
		return (1);
	return (0);
}

void	map_validation(char ***map_str)
{
	char	**map;
	size_t	i;

	map = *map_str;
	i = 0;
	while (map[i])
	{
		if (map_validations(map, i))
		{
			free_str_arr_to_end(map);
			*map_str = NULL;
			return ;
		}
		i++;
	}
	if (has_invalid_path(map, col_counter(map[0]), i))
	{
		free_str_arr_to_end(map);
		*map_str = NULL;
		return ;
	}
}
