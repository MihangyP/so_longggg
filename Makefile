### ARGS
NAME = so_long
SRC = main.c errors.c map_manip.c free.c draw_map.c
SRC_FILES = $(addprefix src/, $(SRC))
CC = cc -g
CFLAGS = -Wall -Wextra ## -Werror
RM = rm -rf

### RULES
all: $(NAME)

$(NAME): $(SRC_FILES)
	make -C ./libft
	$(CC) $(CFLAGS) -I./include -I./raylib/include -o $(NAME) $(SRC_FILES) -Llibft -lft -Lraylib/lib -l:libraylib.a -lm

clean:
	make -C ./libft clean
	$(RM) *.o

fclean: clean
	make -C ./libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
