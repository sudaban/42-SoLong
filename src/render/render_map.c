/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:52:50 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/22 13:11:11 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../allocation/allocation.h"
#include "../../include/so_long.h"
#include "../../libraries/mlx/mlx.h"

void	render_map(t_game *god_obj)
{
	t_game	*g;
	size_t	x;
	size_t	y;
	void	*texture;

	g = god_obj;
	x = 0;
	y = 0;
	if (!g || !g->map_obj || !g->res_obj || !g->mlx_obj)
		safe_exit(1, ERROR_ALLOCATION);
	while (g->map_obj->grid[y])
	{
		x = 0;
		while (g->map_obj->grid[y][x])
		{
			char tile = g->map_obj->grid[y][x];

			if (tile == '1')
				texture = g->res_obj->wall_texture;
			else if (tile == 'P')
				texture = g->res_obj->player_texture;
			else if (tile == 'C')
				texture = g->res_obj->collectible_texture;
			else if (tile == 'E')
				texture = g->res_obj->exit_texture;
			else
				texture = g->res_obj->background_texture;
			mlx_put_image_to_window(g->mlx_obj, g->res_obj->window,
				texture, x * 64, y * 64);
			x++;
		}
		y++;
	}
}
