/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:09:42 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/15 20:24:06 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

# ifndef ESC_KEY
#  define ESC_KEY 65307
# endif

# ifndef W_KEY
#  define W_KEY 119
# endif

# ifndef S_KEY
#  define S_KEY 115
# endif

# ifndef A_KEY
#  define A_KEY 97
# endif

# ifndef D_KEY
#  define D_KEY 100
# endif

# ifndef TILE_SIZE
#  define TILE_SIZE 64
# endif

typedef struct s__pr_err_config
{
	size_t			*map_rows_max;
	const char		*valid_fl_ext;

	// Error messages
	const char		*pr_arg_err_msg;
	const char		*fl_ext_err_msg;
	const char		*fl_empty_err_msg;
	const char		*fl_too_larg_err_msg;
	const char		*no_such_file;
}					t_pr_err_config;

typedef struct s_map_err_config
{
	const char		*map_chars;

	// Error messages
	const char		*invalid_char_err_msg;
	const char		*invalid_content_err_msg;
	const char		*map_not_rec_err_msg;
	const char		*only_empty_rows_err_msg;
	const char		*not_enclosed_by_walls_err_msg;
	const char		*invalid_path_err_msg;
	const char		*map_too_wide_err_msg;
}					t_map_err_config;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	char			**map;
	void			*wall;
	void			*space;
	void			*exit;
	void			*coin;
	void			*player;
	t_point			*position;
	size_t			moves;
	int				is_over;
}					t_game;

// Validation
int					pr_start_validations(int argc, char **argv);

// Config (Global var simulation)
t_pr_err_config		*init_input_err_config(t_pr_err_config *c);
t_pr_err_config		*input_err_config(void);
t_map_err_config	*init_map_err_config(t_map_err_config *c);
t_map_err_config	*map_err_config(void);

// File error handling
void				file_is_empty_handler(char ***map_str);
void				file_is_too_large_handler(char ***map_str, size_t size,
						char *line);
void				no_such_file_handler(void);
void				invalid_path(void);
void				map_too_wide_handler(void);

// Map error handling
void				not_rectangular_handler(void);
void				only_empty_rows_handler(void);
void				not_enclosed_by_walls_handler(void);
void				invalid_char_handler(void);
void				invalid_content_handler(void);

// Memory dealocation utils
void				free_str_arr(char **str_arr, size_t size);
void				free_str_arr_to_end(char **str_arr);
void				free_input_err_config(void);
void				free_configs(void);
void				free_game(t_game *game);

// Map validation
void				map_validation(char ***map_str);

// Map validation functions
int					consists_of_invalid_chars(char *map_row);
int					is_not_rectangular(char *map_row, size_t i);
int					is_not_enclosed_by_walls(char *map_row, size_t i, int col_c,
						int is_last_row);
int					consists_of_invalid_content(char *map_row, int is_last_row);
int					has_invalid_path(char **map_str, int col_c, int row_c);

// Map utils
void				create_map_structure(int fd, char ***map_str, size_t *rowc);
void				print_map(char **map_str);
char				**copy_map(char **map, int row_c);

// Map validation utils
int					col_counter(char *row);
size_t				invalid_char(char c);
int					flood_fill(char **area, t_point *size, t_point *begin);
t_point				*find_position(char **map_str, char target);

// Game
int					launch_game(char **map, size_t rowc);
int					draw_game(t_game *game);

// Game utils
t_game				*init_game(void *mlx, void *win, char **map);
int					is_coin_left(t_game *game);

// Window open and close utils
int					close_win(void *param);
int					handle_key(int keycode, void *param);
int					get_map_w(char **map);
int					get_map_h(size_t rowc);

// Game actions
void				move_up(t_game *game);
void				move_down(t_game *game);
void				move_left(t_game *game);
void				move_right(t_game *game);

#endif