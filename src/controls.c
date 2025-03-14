/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:49:43 by sdaban            #+#    #+#             */
/*   Updated: 2025/03/06 12:03:00 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	move_player(t_game *game, int line, int col)
{
	if (game->map->temp_map[line][col] == '1')
		return (0);
	set_player_position(game->map, line, col);
	return (1);
}

static int	process_key(int key, t_game *game)
{
	int	temp_line;
	int	temp_col;

	temp_line = game->map->player_line;
	temp_col = game->map->player_col;
	if (key == UP)
		temp_line--;
	else if (key == DOWN)
		temp_line++;
	else if (key == LEFT)
		temp_col--;
	else if (key == RIGHT)
		temp_col++;
	else
		return (0);
	return (move_player(game, temp_line, temp_col));
}

int	handle_keys(int key, t_game *game)
{
	if (key == ESC)
		clean_and_exit(game, "Closing Program...", 1);
	if (!process_key(key, game))
		return (0);
	if (is_collectible(game))
	{
		game->map->temp_map[game->map->player_line]
		[game->map->player_col] = '0';
		game->map->collectible--;
	}
	print_move_count(game->move_count++);
	if (game->map->temp_map[game->map->player_line]
		[game->map->player_col] == 'E'
		&& game->map->collectible == 0)
		clean_and_exit(game, "You finished the game.", 1);
	render_map(game);
	render_player(game);
	return (0);
}
