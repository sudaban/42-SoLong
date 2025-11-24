/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:29:17 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/24 10:47:03 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
#include "../../libraries/gnl/get_next_line.h"
#include "../../libraries/libft/libft.h"
#include "../allocation/allocation.h"
#include "map.h"

char	*read_entire_file(int fd)
{
	char	*content;
	char	*line;
	char	*new_content;

	if (fd < 0)
		return (NULL);
	content = NULL;
	line = get_next_line(fd);
	while (line)
	{
		new_content = append_line(content, line);
		memory_free(line);
		if (!new_content)
			return (NULL);
		content = new_content;
		line = get_next_line(fd);
	}
	return (content);
}

static void	check_enclosed_by_walls(t_map *map)
{
	size_t	x;
	size_t	y;

	if (!map || !map->grid)
		safe_exit(1, ERROR_MAP);
	x = 0;
	while (x < map->width)
	{
		if (map->grid[0][x] != '1' || map->grid[map->height - 1][x] != '1')
			safe_exit(1, ERROR_WALLS);
		x++;
	}
	y = 0;
	while (y < map->height)
	{
		if (map->grid[y][0] != '1' || map->grid[y][map->width - 1] != '1')
			safe_exit(1, ERROR_WALLS);
		y++;
	}
}

static void	parse_map_chars(t_map *map)
{
	size_t	x;
	size_t	y;
	size_t	counts[3];

	if (!map || !map->grid)
		safe_exit(1, ERROR_MAP);
	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	map->wall_count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			_process_char(map, x, y, counts);
			x++;
		}
		y++;
	}
	map->start_pos = counts[0];
	map->exit_pos = counts[1];
	map->collectibles = counts[2];
	_check_map_counts(map);
}

char	**dup_grid(char **grid, size_t height, size_t width)
{
	char	**copy;
	size_t	i;

	if (!grid)
		return (NULL);
	copy = memory_malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = memory_malloc(width + 1);
		if (!copy[i])
		{
			free_grid_partial(copy, i);
			return (NULL);
		}
		ft_memcpy(copy[i], grid[i], width);
		copy[i][width] = '\0';
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	validate_map(t_map *map)
{
	if (!map)
		safe_exit(1, ERROR_MAP);
	if (map->height == 0 || map->width == 0)
		safe_exit(1, "Error\nMap is empty");
	check_enclosed_by_walls(map);
	parse_map_chars(map);
	check_path_exists(map);
	ft_putstr_fd("Map validation passed.\n", 1);
}
