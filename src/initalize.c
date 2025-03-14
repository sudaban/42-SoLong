/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:49:35 by sdaban            #+#    #+#             */
/*   Updated: 2025/03/06 12:05:58 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../vendor/libft/libft.h"
#include "../vendor/mlx/mlx.h"
#include <stdlib.h>

t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		clean_and_exit(NULL, "Memory allocation error.", 0);
	game->map = NULL;
	game->graphics = NULL;
	game->move_count = 1;
	return (game);
}

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		clean_and_exit(NULL, "Memory allocation error.", 0);
	ft_memset(map, 0, sizeof(t_map));
	return (map);
}

t_resources	*init_graphics(void)
{
	t_resources	*resource;

	resource = malloc(sizeof(t_resources));
	if (!resource)
		clean_and_exit(NULL, "Memory allocation error.", 0);
	ft_memset(resource, 0, sizeof(resource));
	return (resource);
}

void	init_mlx_and_create_window(t_game *game)
{
	game->graphics->mlx = mlx_init();
	if (!game->graphics->mlx)
		clean_and_exit(game, "Failed to initialize MLX.", 0);
	game->graphics->window = mlx_new_window(game->graphics->mlx,
			game->map->cols * 64, game->map->line * 64, "So Long Console");
}
