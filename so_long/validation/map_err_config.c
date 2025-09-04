/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_err_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:22:31 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/15 20:19:13 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_map_err_config	*init_map_err_config(t_map_err_config *c)
{
	static t_map_err_config	*config;

	if (NULL == c)
		return (config);
	c->map_chars = "01CEP";
	c->invalid_char_err_msg = "Error\nInvalid character\n";
	c->map_not_rec_err_msg = "Error\nMap is not rectangular\n";
	c->only_empty_rows_err_msg = "Error\nMap has only empty rows\n";
	c->not_enclosed_by_walls_err_msg = "Error\nMap is not enclosed by walls\n";
	c->invalid_content_err_msg = "Error\nMap has invalid content\n";
	c->invalid_path_err_msg = "Error\nThere is no valid path in the map\n";
	c->map_too_wide_err_msg = "Error\nMap is too wide to be displayed\n";
	config = c;
	return (config);
}

t_map_err_config	*map_err_config(void)
{
	return (init_map_err_config(NULL));
}
