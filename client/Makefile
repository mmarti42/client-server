NAME = client

SRC = client.c\
	bubble_sort.c\
	support_func.c\
	parse_string.c\
	get_next_line.c

OBJ	= $(SRC:.c=.o)

# project header
HEADER = client.h
HEADERS_DIR = .

# mlx library
GCC = gcc

FLAGS = -Wall -Wextra -Werror

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
