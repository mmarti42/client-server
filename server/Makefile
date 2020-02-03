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

FLAGS = -Wall -Wextra -Werror

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
