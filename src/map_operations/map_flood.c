/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:33:44 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/22 17:11:38 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include "../allocation/allocation.h"
#include "map.h"

void	dfs(t_flood *f, int x, int y)
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

void	init_flood_struct(t_flood *f, char **grid, t_map *map, int *elem)
{
	f->grid = grid;
	f->height = map->height;
	f->width = map->width;
	f->elements = elem;
}
