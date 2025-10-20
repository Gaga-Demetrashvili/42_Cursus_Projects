NAME = minishell

SRC = ./src/tokenization/tokenizer.c\
	./src/tokenization/handle_operator_case.c\
	./src/tokenization/handle_quote_case.c\
	./src/tokenization/token_utils.c\
	./src/utils/expand_envs.c\
	./src/utils/expand_wildcards.c\
	./src/utils/create_nodes.c\
	./src/parse/parse.c\
	./src/parse/parse_utils.c\
	./src/execution/execute.c\
	./src/execution/execute_utils.c\
	./src/execution/execute_heredoc.c\
	./src/execution/execute_pipe.c\
	minishell.c\
	debugging_helpers.c\
	./src/libft/ft_itoa.c\
	./src/libft/ft_strlen.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -g -O0 -Wall -Wextra -Werror

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