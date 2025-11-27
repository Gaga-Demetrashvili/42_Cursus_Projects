NAME = megaphone

SRC = megaphone.cpp

OBJ = $(SRC:.cpp=.o)

CPP = c++

CPP_FLAGS = -Wall -Wextra -Werror -std=c++98

DEPENDENCIES = Makefile

all: $(NAME)

%.o: %.cpp $(DEPENDENCIES)
	$(CPP) $(CPP_FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CPP) $(CPP_FLAGS) $(OBJ) -o $(NAME)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
