NAME = philo_bonus

SRC =	dinner_bonus.c \
	getters_setters_bonus.c \
	init_bonus.c \
	main_bonus.c \
	parsing_bonus.c \
	safe_functions_bonus.c \
	synchro_utils_bonus.c \
	utils_bonus.c \
	write_bonus.c \
	monitor_bonus.c

BONUS_OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread

all: $(NAME)

$(NAME): $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(NAME)

clean:
	rm -f $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
