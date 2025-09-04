NAME = push_swap

LIBFT_DIR = Libft
PRINTF_DIR = ft_printf

LIBFT_MAKE = make bonus -C $(LIBFT_DIR)
PRINTF_MAKE = make -C $(PRINTF_DIR)

LIBFT_A = $(LIBFT_DIR)/libft.a
PRINTF_A = $(PRINTF_DIR)/ft_printf.a

SRC = push_swap.c\
	stack_operations.c\
	utils.c\
	validation.c\
	stack_operations_utils.c\
	sort.c\
	main.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

all: $(LIBFT_A) $(PRINTF_A) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(PRINTF_A) -o $(NAME)

$(LIBFT_A):
	$(LIBFT_MAKE)

$(PRINTF_A):
	$(PRINTF_MAKE)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
