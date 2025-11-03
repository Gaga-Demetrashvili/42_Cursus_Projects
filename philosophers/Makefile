NAME = philo

SRC = \
	mandatory/dinner.c \
	mandatory/getters_setters.c \
	mandatory/init.c \
	mandatory/main.c \
	mandatory/parsing.c \
	mandatory/safe_functions.c \
	mandatory/synchro_utils.c \
	mandatory/utils.c \
	mandatory/write.c \
	mandatory/monitor.c

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