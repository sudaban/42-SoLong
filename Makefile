NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libraries/libft/libft.a
MINILIBX = libraries/mlx/libmlx.a
MLXFLAG = -lXext -lX11 -lm

SRC =	so_long.c src/allocation/allocation.c src/allocation/safe_exit.c \
		src/map_operations/control.c src/map_operations/map.c \
		src/init/initalize.c src/map_operations/map_utils.c \
		libraries/gnl/get_next_line.c libraries/gnl/get_next_line_utils.c \
		src/texture/texture.c src/render/render.c src/allocation/safe_exit_mlx.c \

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(MINILIBX) $(MLXFLAG)

$(LIBFT):
	make -C libraries/libft

$(MINILIBX):
	make -C libraries/mlx

clean:
	rm -f $(OBJ)
	make -C libraries/libft clean

fclean: clean
	rm -f $(NAME)
	make -C libraries/libft fclean
	make -C libraries/mlx clean

re: fclean all

.PHONY: all clean fclean re