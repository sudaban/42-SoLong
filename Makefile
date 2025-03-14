NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = vendor/libft/libft.a
MINILIBX = vendor/mlx/libmlx.a
MLXFLAG = -lXext -lX11 -lm

SRC = src/main.c \
	src/cleaner.c \
	src/controls.c \
	src/resources.c \
	src/initalize.c \
	src/control_map.c \
	src/handle_map.c \
	src/validation.c \
	src/utils.c \
	src/extra.c \
	vendor/gnl/get_next_line.c \
	vendor/gnl/get_next_line_utils.c 

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