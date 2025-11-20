NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = vendor/libft/libft.a
MINILIBX = vendor/mlx/libmlx.a
MLXFLAG = -lXext -lX11 -lm

SRC =	so_long.c src/allocation/allocation.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(MINILIBX) $(MLXFLAG)

$(LIBFT):
	make -C vendor/libft

$(MINILIBX):
	make -C vendor/mlx

clean:
	rm -f $(OBJ)
	make -C vendor/libft clean

fclean: clean
	rm -f $(NAME)
	make -C vendor/libft fclean
	make -C vendor/mlx clean

re: fclean all

.PHONY: all clean fclean re