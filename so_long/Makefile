NAME = so_long

LIBFT_DIR = libft
LIBFT_MAKE = make -C $(LIBFT_DIR)
LIBFT_A = $(LIBFT_DIR)/libft.a

FT_PRINTF_DIR = ft_printf
FT_PRINTF_MAKE = make -C $(FT_PRINTF_DIR)
FT_PRINTF_A = $(FT_PRINTF_DIR)/libftprintf.a

LIBMLX_A = minilibx-linux/libmlx.a

SRC = main.c\
	get_next_line/get_next_line.c\
	get_next_line/get_next_line_utils.c\
	validation/input_validations.c\
	validation/file_err_handling.c\
	validation/map_err_handling.c\
	mem_dealoc_utils.c\
	validation/input_err_config.c\
	validation/map_validation.c\
	validation/map_validation_functions.c\
	validation/map_validation_utils.c\
	validation/map_err_config.c\
	map_utils.c\
	game.c\
	window_open_close.utils.c\
	game_utils.c\
	game_actions.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
MLX_FLAGS = -L/usr/X11/lib -lX11 -lXext -lm

all: mlx $(LIBFT_A) $(FT_PRINTF_A) $(NAME) 

mlx:
	@git clone https://github.com/42Paris/minilibx-linux.git ./minilibx-linux; \
	make -C ./minilibx-linux
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(FT_PRINTF_A) $(LIBMLX_A) $(MLX_FLAGS) -o $(NAME)

$(LIBFT_A):
	$(LIBFT_MAKE)

$(FT_PRINTF_A):
	$(FT_PRINTF_MAKE)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)
	make clean -C $(FT_PRINTF_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(FT_PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re bonus