/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:22:55 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/20 16:48:53 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stddef.h>

# define KEY_ESC 65307
# define KEY_UP 119
# define KEY_DOWN 115
# define KEY_LEFT 97
# define KEY_RIGHT 100

# define ERROR_ARGC "Error\nInvalid number of arguments\n"
# define ERROR_MAP "Error\nInvalid map\n"
# define ERROR_EXTENSION "Error\nInvalid file extension\n"
# define ERROR_ALLOCATION "Error\nMemory allocation failed\n"

typedef struct s_map
{
	char	**grid;
	size_t	width;
	size_t	height;
	size_t	player_x;
	size_t	player_y;
	size_t	collectibles;
	size_t 	exit_pos;
	size_t	start_pos;
	size_t	wall_count;
}	t_map;

typedef struct s_player
{
	int		step_count;
}	t_player;

typedef struct s_game
{
	t_map	*map_obj;
	void	*mlx_obj;
}	t_game;

t_map	*init_map(void);
t_game	*init_game(void);
void	check_file_name(const char *filename);
void	load_map_data(t_map *map, const char *filename);
#endif //SO_LONG_H