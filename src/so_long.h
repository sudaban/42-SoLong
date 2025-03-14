/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:49:08 by sdaban            #+#    #+#             */
/*   Updated: 2025/03/06 12:07:24 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define ESC 65307
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100

typedef struct s_map
{
	char	**temp_map;
	int		collectible;
	int		exit;
	int		start;
	int		wall;
	int		line;
	int		cols;
	int		player_line;
	int		player_col;
}	t_map;

typedef struct s_resources {
	void	*mlx;
	void	*window;
	void	*wall_image;
	void	*player_image;
	void	*collectible_image;
	void	*empty_image;
	void	*door_image;
}	t_resources;

typedef struct s_game
{
	t_map		*map;
	t_resources	*graphics;
	int			move_count;
}	t_game;

t_game		*init_game(void);
t_map		*init_map(void);
t_resources	*init_graphics(void);

int			handle_keys(int key, t_game *game);
int			compare_2_str(char *s1, char *s2);
int			is_collectible(t_game *game);
int			close_window(t_game *game);

void		clean_and_exit(t_game *game, char *msg, int flag);
void		free_double_ptr(char **ptr, int indez);
void		check_valid_path(t_game *game);
void		check_is_rect(t_game *game);
void		map_value_controller(t_game *game);
void		map_wall_controller(t_game *game, char **str);
void		map_loader(char *map, t_game *game);
void		filename_checker(char *str);
void		*load_image(t_game *game, char *path);
void		handle_xpm(t_game *game);
void		init_mlx_and_create_window(t_game *game);
void		*edit_tile(t_game *game, int tile);
void		render_map(t_game *game);
void		render_player(t_game *game);
void		set_player_position(t_map *map, int l, int c);
void		print_move_count(int count);

#endif