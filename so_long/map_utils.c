/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:23:01 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/15 19:47:50 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	create_map_structure(int fd, char ***map_str, size_t *rowc)
{
	char	*line;

	*map_str = malloc(sizeof(char *) * 21);
	if (NULL == map_str)
		return ;
	line = get_next_line(fd);
	if (NULL == line)
		return (file_is_empty_handler(map_str));
	while (line)
	{
		if (*rowc == *(input_err_config()->map_rows_max))
			return (file_is_too_large_handler(map_str, *rowc, line));
		(*map_str)[*rowc] = line;
		line = get_next_line(fd);
		(*rowc)++;
	}
	(*map_str)[*rowc] = NULL;
}

char	**copy_map(char **map, int row_c)
{
	int		i;
	char	**map_dup;
	char	*dup_row;

	i = 0;
	map_dup = (char **)malloc(sizeof(char *) * (row_c + 1));
	if (NULL == map_dup)
		return (NULL);
	while (i < row_c)
	{
		dup_row = ft_strdup(map[i]);
		if (NULL == dup_row)
		{
			free_str_arr(map_dup, i);
			return (NULL);
		}
		else
			map_dup[i] = dup_row;
		i++;
	}
	map_dup[i] = NULL;
	return (map_dup);
}

t_point	*find_position(char **map_str, char target)
{
	int		r;
	int		c;
	t_point	*start_position;

	r = 0;
	c = 0;
	start_position = (t_point *)malloc(sizeof(t_point));
	if (NULL == start_position)
		return (NULL);
	while (map_str[r])
	{
		while (map_str[r][c])
		{
			if (map_str[r][c] == target)
			{
				start_position->x = c;
				start_position->y = r;
				return (start_position);
			}
			c++;
		}
		c = 0;
		r++;
	}
	return (NULL);
}

void	print_map(char **map_str)
{
	size_t	i;

	i = 0;
	while (map_str[i])
	{
		ft_putstr_fd(map_str[i], 1);
		i++;
	}
}
