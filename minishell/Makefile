NAME = minishell

SRC = ./src/frontend/tokenization/tokenizer.c\
	./src/frontend/tokenization/handle_operator_case.c\
	./src/frontend/tokenization/handle_quote_case.c\
	./src/frontend/tokenization/token_utils.c\
	./src/frontend/expand.c\
	parse.c\
	create_nodes.c\
	minishell.c\
	wildcards_handler.c\
	execute.c\
	debugging_helpers.c\
	./src/libft/ft_itoa.c\
	./src/libft/ft_strlen.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

READLINEFLAG = -lreadline

all: $(NAME)

$(NAME) : $(OBJ)
	${CC} ${CFLAGS} $(OBJ) ${READLINEFLAG} -o $(NAME) 
	
clean:
	rm -f $(OBJ) $(B_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:	all clean fclean re bonus