/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:29:34 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/22 14:02:29 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include "../allocation/allocation.h"
#include "../../libraries/mlx/mlx.h"
#include "../../libraries/libft/libft.h"
#include "move_helpers.h"

int	handle_close(t_game *game)
{
	finish_and_clean(game);
	return (0);
}

static int	process_key(int key, t_game *game)
{
	int	ny;
	int	nx;

	if (!game || !game->map_obj)
		return (0);
	ny = (int)game->map_obj->player_y;
	nx = (int)game->map_obj->player_x;
	if (key == KEY_UP)
		ny--;
	else if (key == KEY_DOWN)
		ny++;
	else if (key == KEY_LEFT)
		nx--;
	else if (key == KEY_RIGHT)
		nx++;
	else
		return (0);
	return (move_player(game, ny, nx));
}

int	handle_key_press(int keycode, t_game *game)
{
	if (!game)
		return (0);
	if (keycode == KEY_ESC)
	{
		finish_and_clean(game);
		return (0);
	}
	if (!process_key(keycode, game))
		return (0);
	game->move_count++;
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(game->move_count, 1);
	ft_putchar_fd('\n', 1);
	render_resources(game);
	return (0);
}
