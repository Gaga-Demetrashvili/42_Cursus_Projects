NAME = philo

SRC = \
	mandatory/actions_utils.c \
	mandatory/actions.c \
	mandatory/main.c \
	mandatory/mutexes.c \
	mandatory/utils.c \
	mandatory/validation.c \
	mandatory/monitor.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus