### ARGS
NAME = so_long
SRC = main.c errors.c catch_map.c
SRC_FILES = $(addprefix src/, $(SRC))
CC = cc
CFLAGS = -Wall -Wextra ## -Werror
RM = rm -rf

### RULES
all: $(NAME)

$(NAME): $(SRC_FILES)
	make -C ./libft
	$(CC) $(CFLAGS) -I./include -o $(NAME) $(SRC_FILES) -Llibft -lft

clean:
	make -C ./libft clean
	$(RM) *.o

fclean: clean
	make -C ./libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
