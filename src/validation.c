/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:49:15 by sdaban            #+#    #+#             */
/*   Updated: 2025/03/06 12:03:18 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

static char	**init_visited(t_game *game)
{
	char	**visited;
	int		i;
	int		j;

	visited = malloc(game->map->line * sizeof(char *));
	if (!visited)
		clean_and_exit(game, "Memory allocation error.", 0);
	i = 0;
	while (i < game->map->line)
	{
		visited[i] = malloc(game->map->cols * sizeof(char));
		if (!visited[i])
		{
			free_double_ptr(visited, i);
			clean_and_exit(game, "Memory allocation error.", 0);
		}
		j = 0;
		while (j < game->map->cols)
		{
			visited[i][j] = game->map->temp_map[i][j];
			j++;
		}
		i++;
	}
	return (visited);
}

static void	dfs(char **str, int *elements, int x, int y)
{
	if (str[x][y] == '1' || *elements == 0)
		return ;
	if (str[x][y] == 'E' || str[x][y] == 'C')
		*elements -= 1;
	str[x][y] = '1';
	dfs(str, elements, x, y + 1);
	dfs(str, elements, x, y - 1);
	dfs(str, elements, x + 1, y);
	dfs(str, elements, x - 1, y);
}

void	check_valid_path(t_game *game)
{
	int		elements;
	char	**visited;

	visited = init_visited(game);
	elements = game->map->collectible + game->map->exit;
	dfs(visited, &elements, game->map->player_line, game->map->player_col);
	if (elements != 0)
	{
		free_double_ptr(visited, game->map->line);
		clean_and_exit(game, "Map path is invalid.", 0);
	}
	free_double_ptr(visited, game->map->line);
}
