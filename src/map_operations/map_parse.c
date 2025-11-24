/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:20:53 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/24 10:37:57 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include "../allocation/allocation.h"
#include "map.h"

void	_process_char(t_map *map, size_t x, size_t y, size_t counts[3])
{
	char	ch;

	ch = map->grid[y][x];
	if (ch == 'P')
	{
		map->player_x = x;
		map->player_y = y;
		counts[0]++;
	}
	else if (ch == 'E')
		counts[1]++;
	else if (ch == 'C')
		counts[2]++;
	else if (ch == '1')
		map->wall_count++;
	else if (ch == '0')
		;
	else
		safe_exit(1, ERROR_CHARACTERS);
}

void	_check_map_counts(t_map *map)
{
	if (map->start_pos != 1)
		safe_exit(1, ERROR_PLAYER);
	if (map->exit_pos != 1)
		safe_exit(1, ERROR_EXIT);
	if (map->collectibles < 1)
		safe_exit(1, ERROR_COLLECTIBLE);
}

static void	dfs(t_flood *f, int x, int y)
{
	if (x < 0 || y < 0)
		return ;
	if ((size_t)x >= f->height || (size_t)y >= f->width)
		return ;
	if (f->grid[x][y] == '1' || *(f->elements) == 0)
		return ;
	if (f->grid[x][y] == 'E' || f->grid[x][y] == 'C')
		(*(f->elements))--;
	f->grid[x][y] = '1';
	dfs(f, x, y + 1);
	dfs(f, x, y - 1);
	dfs(f, x + 1, y);
	dfs(f, x - 1, y);
}

static void	init_flood_struct(t_flood *f, char **grid, t_map *map, int *elem)
{
	f->grid = grid;
	f->height = map->height;
	f->width = map->width;
	f->elements = elem;
}

void	check_path_exists(t_map *map)
{
	char	**copy;
	int		elements;
	t_flood	f_data;

	if (!map || !map->grid)
		safe_exit(1, ERROR_MAP);
	copy = dup_grid(map->grid, map->height, map->width);
	if (!copy)
		safe_exit(1, ERROR_ALLOCATION);
	elements = (int)map->collectibles + (int)map->exit_pos;
	init_flood_struct(&f_data, copy, map, &elements);
	dfs(&f_data, (int)map->player_y, (int)map->player_x);
	free_grid(copy, map->height);
	if (elements != 0)
		safe_exit(1, ERROR_MAP_PATH);
}
