/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:29:06 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/22 12:48:58 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include "../allocation/allocation.h"
#include "../../libraries/mlx/mlx.h"

static void	*load_texture(t_game *g, const char *path)
{
	int		w;
	int		h;
	void	*img;

	if (!g || !g->mlx_obj)
		safe_exit(1, ERROR_ALLOCATION);
	img = mlx_xpm_file_to_image(g->mlx_obj, (char *)path, &w, &h);
	if (!img)
		safe_exit(1, ERROR_TEXTURE);
	return (img);
}

void	set_textures(t_game *god_obj)
{
	t_game	*g;

	g = god_obj;
	if (!g || !g->res_obj)
		safe_exit(1, ERROR_ALLOCATION);
	g->res_obj->wall_texture = load_texture(g, "textures/wall.xpm");
	g->res_obj->player_texture = load_texture(g, "textures/player.xpm");
	g->res_obj->collectible_texture = load_texture(g, "textures/lock.xpm");
	g->res_obj->background_texture = load_texture(g, "textures/background.xpm");
	g->res_obj->exit_texture = load_texture(g, "textures/door.xpm");
}
