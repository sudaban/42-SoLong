/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:52:50 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/22 13:25:57 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include "../allocation/allocation.h"
#include "../../libraries/mlx/mlx.h"

static void	*texture_for_tile(t_game *g, char tile)
{
	if (!g || !g->res_obj)
		return (NULL);
	if (tile == '1')
		return (g->res_obj->wall_texture);
	if (tile == 'P')
		return (g->res_obj->player_texture);
	if (tile == 'C')
		return (g->res_obj->collectible_texture);
	if (tile == 'E')
		return (g->res_obj->exit_texture);
	return (g->res_obj->background_texture);
}

static void	draw_tile(t_game *g, size_t x, size_t y, void *texture)
{
	int	px;
	int	py;

	if (!g || !g->mlx_obj || !g->res_obj || !texture)
		return ;
	px = (int)(x * 64);
	py = (int)(y * 64);
	mlx_put_image_to_window(g->mlx_obj, g->res_obj->window, texture, px, py);
}

static void	draw_player_at(t_game *g)
{
	int	px;
	int	py;

	if (!g || !g->map_obj || !g->res_obj || !g->mlx_obj)
		return ;
	px = (int)(g->map_obj->player_x * 64);
	py = (int)(g->map_obj->player_y * 64);
	if (g->map_obj->grid[g->map_obj->player_y][g->map_obj->player_x] == 'E')
		mlx_put_image_to_window(g->mlx_obj, g->res_obj->window,
			g->res_obj->exit_texture, px, py);
	if (g->res_obj->player_texture)
		mlx_put_image_to_window(g->mlx_obj, g->res_obj->window,
			g->res_obj->player_texture, px, py);
}

void	render_resources(t_game *god_obj)
{
	t_game	*g;
	size_t	x;
	size_t	y;
	char	*row;

	g = god_obj;
	if (!g || !g->map_obj || !g->res_obj || !g->mlx_obj)
		safe_exit(1, ERROR_ALLOCATION);
	y = 0;
	row = g->map_obj->grid[y];
	while (row)
	{
		x = 0;
		while (row[x])
		{
			draw_tile(g, x, y, texture_for_tile(g, row[x]));
			x++;
		}
		y++;
		row = g->map_obj->grid[y];
	}
	draw_player_at(g);
}
