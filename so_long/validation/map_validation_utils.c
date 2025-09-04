/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:23:12 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/15 20:31:54 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	col_counter(char *row)
{
	int	i;

	i = 0;
	while (row[i] && row[i] != '\n')
		i++;
	return (i);
}

size_t	invalid_char(char c)
{
	const char	*valid_chars;
	size_t		i;

	valid_chars = map_err_config()->map_chars;
	i = 0;
	while (valid_chars[i])
	{
		if (c == valid_chars[i])
			return (0);
		i++;
	}
	return (1);
}

static void	fill(char **area, t_point *size, int row, int col)
{
	if (area[row][col] == 'V' || area[row][col] == '1' || area[row][col] == 'E')
		return ;
	area[row][col] = 'V';
	fill(area, size, row - 1, col);
	fill(area, size, row + 1, col);
	fill(area, size, row, col - 1);
	fill(area, size, row, col + 1);
}

static int	is_unfiled_space(char **area)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (area[y])
	{
		while (area[y][x])
		{
			if (area[y][x] && area[y][x] != '\n' && area[y][x] != '1'
				&& area[y][x] != 'V' && area[y][x] != 'E')
				return (1);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int	flood_fill(char **area, t_point *size, t_point *begin)
{
	t_point	*exit_position;
	int		result;
	char	**copied_area;

	copied_area = copy_map(area, size->y);
	exit_position = find_position(area, 'E');
	result = 0;
	fill(copied_area, size, begin->y, begin->x);
	if (is_unfiled_space(copied_area))
		result = 1;
	free(exit_position);
	free_str_arr_to_end(copied_area);
	return (result);
}
