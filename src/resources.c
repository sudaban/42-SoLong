/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:49:39 by sdaban            #+#    #+#             */
/*   Updated: 2025/03/06 12:03:14 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../vendor/mlx/mlx.h"

void	handle_xpm(t_game *game)
{
	game->graphics->wall_image = load_image(game, "./textures/wall.xpm");
	game->graphics->player_image = load_image(game, "./textures/player.xpm");
	game->graphics->collectible_image = load_image(game,
			"./textures/lock.xpm");
	game->graphics->empty_image = load_image(game, "./textures/background.xpm");
	game->graphics->door_image = load_image(game, "./textures/door.xpm");
}

void	render_map(t_game *game)
{
	int		col;
	int		line;
	void	*img;

	line = 0;
	while (game->map->temp_map[line])
	{
		col = 0;
		while (game->map->temp_map[line][col])
		{
			img = edit_tile(game, game->map->temp_map[line][col]);
			mlx_put_image_to_window(game->graphics->mlx,
				game->graphics->window, img, col * 64, line * 64);
			col++;
		}
		line++;
	}
}

void	render_player(t_game *game)
{
	if (game->map->temp_map[game->map->player_line]
		[game->map->player_col] == 'E')
	{
		mlx_put_image_to_window(game->graphics->mlx, game->graphics->window,
			game->graphics->door_image, game->map->player_col * 64,
			game->map->player_line * 64);
	}
	mlx_put_image_to_window(game->graphics->mlx, game->graphics->window,
		game->graphics->player_image, game->map->player_col * 64,
		game->map->player_line * 64);
}
