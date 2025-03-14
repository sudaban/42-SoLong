/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:49:47 by sdaban            #+#    #+#             */
/*   Updated: 2025/03/06 12:05:32 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../vendor/mlx/mlx.h"
#include "../vendor/libft/libft.h"
#include <stdlib.h>

void	free_double_ptr(char **ptr, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

static void	mlx_cleaner(t_resources *graphics)
{
	if (graphics->collectible_image)
		mlx_destroy_image(graphics->mlx, graphics->collectible_image);
	if (graphics->empty_image)
		mlx_destroy_image(graphics->mlx, graphics->empty_image);
	if (graphics->door_image)
		mlx_destroy_image(graphics->mlx, graphics->door_image);
	if (graphics->player_image)
		mlx_destroy_image(graphics->mlx, graphics->player_image);
	if (graphics->wall_image)
		mlx_destroy_image(graphics->mlx, graphics->wall_image);
	if (graphics->window)
		mlx_destroy_window(graphics->mlx, graphics->window);
	if (graphics->mlx)
	{
		mlx_destroy_display(graphics->mlx);
		free(graphics->mlx);
	}
}

static void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->temp_map)
	{
		while (map->temp_map[i])
		{
			free(map->temp_map[i]);
			i++;
		}
		free(map->temp_map);
	}
	free(map);
}

void	clean_and_exit(t_game *game, char *msg, int flag)
{
	if (game)
	{
		if (game->graphics)
		{
			mlx_cleaner(game->graphics);
			free(game->graphics);
		}
		if (game->map)
			free_map(game->map);
		free(game);
	}
	if (flag != 1)
		ft_putstr_fd("Error\n", 1);
	ft_putendl_fd(msg, 1);
	exit(0);
}
