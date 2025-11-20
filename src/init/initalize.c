/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:27:13 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/20 16:49:00 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include "../allocation/allocation.h"

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
	return (game);
}
