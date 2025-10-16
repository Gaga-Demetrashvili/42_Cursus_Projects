NAME = minishell

SRC = create_nodes.c\
	tokenizer.c\
	parse.c\
	minishell.c\
	expand.c\
	wildcards_handler.c\
	token_utils.c\
	execute.c\
	debugging_helpers.c

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