/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:49:20 by sdaban            #+#    #+#             */
/*   Updated: 2025/03/06 12:07:35 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../vendor/gnl/get_next_line.h"
#include "../vendor/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void	map_line_calc(char *filename, t_game *game)
{
	char	*tmp;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd <= -1)
		clean_and_exit(game, "FD Error", 0);
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		game->map->line++;
		free(tmp);
		tmp = get_next_line(fd);
	}
	free(tmp);
	close(fd);
	game->map->temp_map = malloc((game->map->line + 1) * sizeof(char *));
	if (!game->map->temp_map)
		clean_and_exit(game, "Memory allocation error.", 0);
}

void	map_loader(char *map, t_game *game)
{
	int		k;
	char	*tmp;
	int		fd;

	k = 0;
	map_line_calc(map, game);
	fd = open(map, O_RDONLY);
	if (fd <= -1)
		clean_and_exit(game, "FD Error", 0);
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		game->map->cols = ft_strlen(tmp);
		game->map->temp_map[k] = malloc(game->map->cols + 1);
		if (!game->map->temp_map[k])
			clean_and_exit(game, "Memory allocation error.", 0);
		ft_memcpy(game->map->temp_map[k], tmp, game->map->cols);
		game->map->temp_map[k][game->map->cols] = '\0';
		k++;
		free(tmp);
		tmp = get_next_line(fd);
	}
	free(tmp);
	close(fd);
	game->map->temp_map[k] = NULL;
}
