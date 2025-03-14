/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:49:30 by sdaban            #+#    #+#             */
/*   Updated: 2025/03/06 12:03:09 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../vendor/mlx/mlx.h"
#include <stdlib.h>
#include <X11/X.h>

static void	map_process(char *map, t_game **game)
{
	filename_checker(map);
	(*game) = init_game();
	(*game)->map = init_map();
	map_loader(map, *game);
	check_is_rect(*game);
	map_value_controller(*game);
}

static void	start_so_long(char *map_file)
{
	t_game	*so_long;
	char	**temp_map;

	so_long = NULL;
	map_process(map_file, &so_long);
	temp_map = so_long->map->temp_map;
	map_wall_controller(so_long, temp_map);
	check_valid_path(so_long);
	so_long->graphics = init_graphics();
	init_mlx_and_create_window(so_long);
	handle_xpm(so_long);
	render_map(so_long);
	render_player(so_long);
	mlx_hook(so_long->graphics->window, KeyPress, KeyPressMask,
		handle_keys, so_long);
	mlx_hook(so_long->graphics->window, 17, 1 << 17L, close_window, so_long);
	mlx_loop(so_long->graphics->mlx);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
		start_so_long(argv[1]);
	else
		clean_and_exit(NULL, "Usage: ./so_long <map_file>", 0);
}
