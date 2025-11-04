NAME = philo_bonus

SRC =	dinner.c \
	getters_setters.c \
	init.c \
	main.c \
	parsing.c \
	safe_functions.c \
	synchro_utils.c \
	utils.c \
	write.c \
	monitor.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
