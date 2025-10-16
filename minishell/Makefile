NAME = minishell

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Source files organized by module
PARSING_SRC = $(SRC_DIR)/parsing/parse.c \
			  $(SRC_DIR)/parsing/parse_utils.c \
			  $(SRC_DIR)/parsing/parse_redirections.c \
			  $(SRC_DIR)/parsing/parse_command.c \
			  $(SRC_DIR)/parsing/create_nodes.c \
			  $(SRC_DIR)/parsing/create_operator_nodes.c

EXECUTION_SRC = $(SRC_DIR)/execution/execute.c \
				$(SRC_DIR)/execution/execute_heredoc.c \
				$(SRC_DIR)/execution/execute_command.c \
				$(SRC_DIR)/execution/execute_setup.c \
				$(SRC_DIR)/execution/execute_pipe.c \
				$(SRC_DIR)/execution/execute_pipe_helpers.c

TOKENIZATION_SRC = $(SRC_DIR)/tokenization/tokenizer.c \
				   $(SRC_DIR)/tokenization/expand.c \
				   $(SRC_DIR)/tokenization/expand_helpers.c \
				   $(SRC_DIR)/tokenization/wildcards_handler.c \
				   $(SRC_DIR)/tokenization/wildcard_helpers.c \
				   $(SRC_DIR)/tokenization/token_utils.c

UTILS_SRC = $(SRC_DIR)/utils/debugging_helpers.c \
			$(SRC_DIR)/utils/debug_print_helpers.c \
			$(SRC_DIR)/utils/ft_gb_collect.c

MAIN_SRC = minishell.c

# All source files
SRC = $(PARSING_SRC) $(EXECUTION_SRC) $(TOKENIZATION_SRC) $(UTILS_SRC) $(MAIN_SRC)

# Object files (mirror source structure in obj/)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ := $(OBJ:%.c=$(OBJ_DIR)/%.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)

READLINEFLAG = -lreadline

all: $(NAME)

# Create necessary directories
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/execution
	@mkdir -p $(OBJ_DIR)/tokenization
	@mkdir -p $(OBJ_DIR)/utils

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(READLINEFLAG) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re