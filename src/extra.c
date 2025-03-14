/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:48:40 by sdaban            #+#    #+#             */
/*   Updated: 2025/03/06 12:02:04 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../vendor/mlx/mlx.h"
#include <stdlib.h>

int	close_window(t_game *game)
{
	clean_and_exit(game, "Program has finished.", 1);
	return (0);
}

void	*load_image(t_game *game, char *path)
{
	int		h;
	int		w;
	void	*img;

	img = mlx_xpm_file_to_image(game->graphics->mlx, path, &w, &h);
	if (!img)
		clean_and_exit(game, "MLX file has an incorrect name.", 0);
	return (img);
}

void	*edit_tile(t_game *game, int tile)
{
	void	*img;

	img = NULL;
	if (tile == '1')
		img = game->graphics->wall_image;
	else if (tile == '0' || tile == 'P')
		img = game->graphics->empty_image;
	else if (tile == 'E')
		img = game->graphics->door_image;
	else if (tile == 'C')
		img = game->graphics->collectible_image;
	if (!img)
		clean_and_exit(game, "Image could not be loaded.", 0);
	return (img);
}
