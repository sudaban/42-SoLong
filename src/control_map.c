/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:49:24 by sdaban            #+#    #+#             */
/*   Updated: 2025/03/06 12:02:54 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../vendor/libft/libft.h"
#include "../vendor/gnl/get_next_line.h"

void	filename_checker(char *str)
{
	char	*tmp;

	tmp = ft_strchr(str, '.');
	if (!tmp)
		clean_and_exit(NULL, "Map file must contain a '.'", 0);
	if (!compare_2_str(tmp, ".ber"))
		clean_and_exit(NULL, "Map file extension must be .ber!", 0);
}

void	check_is_rect(t_game *game)
{
	int	l;

	l = 0;
	while (game->map->temp_map[l])
	{
		if (gnl_strlen(game->map->temp_map[l]) != game->map->cols)
			clean_and_exit(game, "Map is not a rectangle.", 0);
		l++;
	}
}

static void	mini_controller(t_game *game, int l, int w)
{
	char	c;

	c = game->map->temp_map[l][w];
	if (c == 'C')
		game->map->collectible++;
	else if (c == 'P')
	{
		game->map->player_line = l;
		game->map->player_col = w;
		game->map->start++;
	}
	else if (c == 'E')
		game->map->exit++;
	else if (game->map->temp_map[l][w] != '0'
		&& game->map->temp_map[l][w] != '1')
		clean_and_exit(game, "Map contains invalid values.", 0);
}

void	map_value_controller(t_game *game)
{
	int	w;
	int	l;

	l = 0;
	while (game->map->temp_map[l])
	{
		w = 0;
		while (game->map->temp_map[l][w])
		{
			mini_controller(game, l, w);
			w++;
		}
		l++;
	}
	if (game->map->exit != 1)
		clean_and_exit (game, "Map does not have an exit.", 0);
	if (game->map->collectible < 1)
		clean_and_exit (game, "Map does not have any collectible", 0);
	if (game->map->start != 1)
		clean_and_exit(game, "Map does not have a player.", 0);
}

void	map_wall_controller(t_game *game, char **str)
{
	int	l;
	int	i;

	l = 0;
	while (str[l])
	{
		i = 0;
		while (str[l][i])
		{
			if (str[0][i] != '1' || str[l][0] != '1'
				|| str[l][game->map->cols - 1] != '1')
				clean_and_exit(game, "Map walls are incorrect.", 0);
			if (l == game->map->line - 1)
			{
				while (str[l][i])
					if (str[l][i++] != '1')
						clean_and_exit(game, "Map walls are incorrect.", 0);
			}
			else
				i++;
		}
		l++;
	}
}
