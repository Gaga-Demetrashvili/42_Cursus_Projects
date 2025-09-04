/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:23:08 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/15 20:23:33 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	consists_of_invalid_chars(char *map_row)
{
	size_t	i;

	i = 0;
	while (map_row[i] && map_row[i] != '\n')
	{
		if (invalid_char(map_row[i]))
		{
			invalid_char_handler();
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_not_rectangular(char *map_row, size_t i)
{
	static int	first_col_c;
	int			next_col_c;

	if (0 == i)
		first_col_c = col_counter(map_row);
	else if (first_col_c > 40)
	{
		map_too_wide_handler();
		return (1);
	}
	else
	{
		next_col_c = col_counter(map_row);
		if (first_col_c != next_col_c)
		{
			not_rectangular_handler();
			return (1);
		}
	}
	if (1 == first_col_c)
	{
		only_empty_rows_handler();
		return (1);
	}
	return (0);
}

int	is_not_enclosed_by_walls(char *map_row, size_t i, int col_c,
		int is_last_row)
{
	size_t	j;
	int		err;

	j = 0;
	err = 0;
	if (i == 0 || is_last_row)
	{
		while (map_row[j] && map_row[j] != '\n')
		{
			if (map_row[j] != '1')
				err = 1;
			j++;
		}
	}
	else if (map_row[0] != '1' || map_row[col_c - 1] != '1')
		err = 1;
	if (err)
	{
		not_enclosed_by_walls_handler();
		return (1);
	}
	return (0);
}

int	consists_of_invalid_content(char *map_row, int is_last_row)
{
	static size_t	start_position;
	static size_t	exit;
	static size_t	collectible;
	size_t			i;

	i = 0;
	while (map_row[i])
	{
		if (map_row[i] == 'C')
			collectible++;
		else if (map_row[i] == 'P')
			start_position++;
		else if (map_row[i] == 'E')
			exit++;
		i++;
	}
	if (is_last_row && (start_position > 1 || start_position == 0 || exit > 1
			|| exit == 0 || collectible == 0))
	{
		invalid_content_handler();
		return (1);
	}
	return (0);
}

int	has_invalid_path(char **map_str, int col_c, int row_c)
{
	t_point	*start_position;
	t_point	*size;

	start_position = find_position(map_str, 'P');
	size = (t_point *)malloc(sizeof(t_point));
	if (NULL == size)
		return (1);
	size->x = col_c - 1;
	size->y = row_c;
	if (NULL == start_position)
		return (1);
	if (flood_fill(map_str, size, start_position))
	{
		invalid_path();
		free(start_position);
		free(size);
		return (1);
	}
	free(start_position);
	free(size);
	return (0);
}
