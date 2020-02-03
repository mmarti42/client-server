NAME = client

SRC = client.c\
	bubble_sort.c\
	support_func.c\
	parse_string.c\

OBJ	= $(SRC:.c=.o)

# project header
HEADER = client.h
HEADERS_DIR = .

# mlx library
GCC = gcc

FLAGS = -Wall -Wextra -Werror -lreadline

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(GCC) $(OBJ) -o $(NAME) $(FLAGS)

$(LIB_FT):
	make -C $(LIB_DIR)

$(MLX_LIB):
	make -C $(MLX_DIR)

%.o: %.c $(HEADER)
	$(GCC) -I $(HEADERS_DIR) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
