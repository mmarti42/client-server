NAME = server

SRC = serv.c\
	parse_sub.c\
	support_func.c\
	get_next_step.c\

OBJ	= $(SRC:.c=.o)

# project header
HEADER = serv.h
HEADERS_DIR = .

# mlx library
GCC = gcc

FLAGS = -Wall -Wextra -Werror -lpthread

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(GCC) $(OBJ) -o $(NAME) $(FLAGS)

%.o: %.c $(HEADER)
	$(GCC) -I $(HEADERS_DIR) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
