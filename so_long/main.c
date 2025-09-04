/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:22:52 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/15 19:49:15 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_and_parse_map(char *filePath)
{
	int		fd;
	char	**map_str;
	size_t	rowc;

	fd = open(filePath, O_RDONLY);
	map_str = NULL;
	rowc = 0;
	if (fd == -1)
	{
		no_such_file_handler();
		return (1);
	}
	create_map_structure(fd, &map_str, &rowc);
	if (NULL == map_str)
		return (1);
	map_validation(&map_str);
	if (NULL == map_str)
		return (1);
	if (launch_game(map_str, rowc))
		return (1);
	free_str_arr_to_end(map_str);
	return (0);
}

int	main(int argc, char **argv)
{
	int	result;

	result = 0;
	init_input_err_config(malloc(sizeof(t_pr_err_config)));
	init_map_err_config(malloc(sizeof(t_map_err_config)));
	if (pr_start_validations(argc, argv))
		result = 1;
	if (!result && load_and_parse_map(argv[1]))
		result = 1;
	free_configs();
	return (result);
}
