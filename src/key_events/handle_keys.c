/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:29:34 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/22 13:48:11 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include "../allocation/allocation.h"
#include "../../libraries/mlx/mlx.h"

int	handle_close(t_game *game)
{
	finish_and_clean(game);
	return (0);
}

static int	move_player(t_game *game, int new_y, int new_x)
{
	t_map	*map;
	char	dest;

	if (!game || !game->map_obj)
		return (0);
	map = game->map_obj;
	if (new_y < 0 || new_x < 0)
		return (0);
	if ((size_t)new_y >= map->height || (size_t)new_x >= map->width)
		return (0);
	dest = map->grid[new_y][new_x];
	if (dest == '1')
		return (0);
	if (dest == 'C')
	{
		if (map->collectibles > 0)
			map->collectibles--;
		map->grid[new_y][new_x] = '0';
	}
	map->grid[map->player_y][map->player_x] = '0';
	if (dest != 'E')
		map->grid[new_y][new_x] = 'P';
	map->player_x = (size_t)new_x;
	map->player_y = (size_t)new_y;
	if (dest == 'E' && map->collectibles == 0)
		finish_and_clean(game);
	return (1);
}

static int	process_key(int key, t_game *game)
{
	int	ny;
	int	nx;

	if (!game || !game->map_obj)
		return (0);
	ny = (int)game->map_obj->player_y;
	nx = (int)game->map_obj->player_x;
	if (key == KEY_UP)
		ny--;
	else if (key == KEY_DOWN)
		ny++;
	else if (key == KEY_LEFT)
		nx--;
	else if (key == KEY_RIGHT)
		nx++;
	else
		return (0);
	return (move_player(game, ny, nx));
}

int	handle_key_press(int keycode, t_game *game)
{
	if (!game)
		return (0);
	if (keycode == KEY_ESC)
	{
		finish_and_clean(game);
		return (0);
	}
	if (!process_key(keycode, game))
		return (0);
	render_resources(game);
	return (0);
}