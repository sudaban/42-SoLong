/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:33:44 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/24 10:37:11 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include "map.h"

void	init_flood_struct(t_flood *f, char **grid, t_map *map, int *elem)
{
	f->grid = grid;
	f->height = map->height;
	f->width = map->width;
	f->elements = elem;
}
