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
	./src/execution/execute_pipe_utils.c\
	./src/builtins/builtin_dispatcher.c\
	./src/builtins/builtin_echo.c\
	./src/builtins/builtin_cd.c\
	./src/builtins/builtin_pwd.c\
	./src/builtins/builtin_env.c\
	./src/builtins/builtin_exit.c\
	./src/builtins/builtin_export.c\
	./src/builtins/builtin_unset.c\
	./src/libft/ft_itoa.c\
	./src/libft/ft_strlen.c\
	./src/libft/ft_strdup.c\
	./src/libft/ft_strndup.c\
	./src/libft/ft_strcmp.c\
	./src/libft/ft_strncmp.c\
	./src/libft/ft_strchr.c\
	minishell.c\

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