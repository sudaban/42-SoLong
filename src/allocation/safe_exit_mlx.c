/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:40:37 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/22 13:41:59 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocation.h"
#include "../../include/so_long.h"
#include "../../libraries/mlx/mlx.h"
#include <unistd.h>
#include <stdlib.h>

static void	clean_every_mlx_object(t_game *game)
{
	t_game		*g;
	void		*images[5];
	size_t		i;

	g = game;
	if (!g || !g->res_obj)
		return ;
	images[0] = g->res_obj->collectible_texture;
	images[1] = g->res_obj->background_texture;
	images[2] = g->res_obj->exit_texture;
	images[3] = g->res_obj->player_texture;
	images[4] = g->res_obj->wall_texture;
	i = 0;
	while (i < 5)
	{
		if (images[i] && g->mlx_obj)
			mlx_destroy_image(g->mlx_obj, images[i]);
		i++;
	}
	if (g->res_obj->window && g->mlx_obj)
		mlx_destroy_window(g->mlx_obj, g->res_obj->window);
	mlx_destroy_display(g->mlx_obj);
	free(g->mlx_obj);
}

void	finish_and_clean(t_game *game)
{
	if (game)
	{
		clean_every_mlx_object(game);
	}
	memory_cleanup(0);
}
