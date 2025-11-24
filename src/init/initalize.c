/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:27:13 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/24 10:52:01 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include "../allocation/allocation.h"
#include "../../libraries/mlx/mlx.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = (t_map *)memory_malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->collectibles = 0;
	map->exit_pos = 0;
	map->start_pos = 0;
	map->wall_count = 0;
	return (map);
}

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)memory_malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->map_obj = NULL;
	game->mlx_obj = NULL;
	game->move_count = 0;
	return (game);
}

t_resource	*init_resources(void)
{
	t_resource	*res;

	res = (t_resource *)memory_malloc(sizeof(t_resource));
	if (!res)
		return (NULL);
	res->window = NULL;
	res->wall_texture = NULL;
	res->player_texture = NULL;
	res->collectible_texture = NULL;
	res->background_texture = NULL;
	res->exit_texture = NULL;
	return (res);
}

void	init_mlx(t_game *god_obj)
{
	t_game	*g;

	g = god_obj;
	if (!g)
		safe_exit(1, ERROR_ALLOCATION);
	g->mlx_obj = mlx_init();
	if (!g->mlx_obj)
		safe_exit(1, ERROR_MLX);
	g->res_obj->window = mlx_new_window(g->mlx_obj,
			g->map_obj->width * 64,
			g->map_obj->height * 64,
			"SOLONGKNK");
}
