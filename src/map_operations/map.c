/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:17:14 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/21 10:42:04 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "../../include/so_long.h"
#include "../../libraries/gnl/get_next_line.h"
#include "../../libraries/libft/libft.h"
#include "../allocation/allocation.h"

static char	*read_entire_file(int fd)
{
	char	*content;
	char	*line;
	char	*temp;
	size_t	len;

	if (fd < 0)
		return (NULL);
	content = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (!content)
		{
			len = ft_strlen(line);
			content = memory_malloc(len + 1);
			if (!content)
			{
				memory_free(line);
				return (NULL);
			}
			ft_memcpy(content, line, len + 1);
		}
		else
		{
			temp = ft_strjoin(content, line);
			memory_free(content);
			if (!temp)
			{
				memory_free(line);
				return (NULL);
			}
			content = temp;
		}
		memory_free(line);
		line = get_next_line(fd);
	}
	return (content);
}

static size_t	count_lines(const char *str)
{
	size_t	count;
	size_t i;

	if (!str || !*str)
		return (0);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			count++;
		i++;
	}
	if (i > 0 && str[i - 1] != '\n')
		count++;
	return (count);
}

static char	**split_into_grid(const char *content, size_t height)
{
	char	**grid;
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	len;

	if (!content)
		return (NULL);
	grid = memory_malloc(sizeof(char *) * (height + 1));
	if (!grid)
		return (NULL);
	i = 0;
	j = 0;
	start = 0;
	len = 0;
	while (content[i])
	{
		if (content[i] == '\n')
		{
			len = i - start;
			grid[j] = memory_malloc(len + 1);
			if (!grid[j])
				return (NULL);
			ft_memcpy(grid[j], &content[start], len);
			grid[j][len] = '\0';
			j++;
			start = i + 1;
		}
		i++;
	}
	if (start < i)
	{
		len = i - start;
		grid[j] = memory_malloc(len + 1);
		if (!grid[j])
			return (NULL);
		ft_memcpy(grid[j], &content[start], len);
		grid[j][len] = '\0';
		j++;
	}
	grid[j] = NULL;
	return (grid);
}


void	load_map_data(t_map *map, const char *filename)
{
	int		fd;
	char	*content;
	size_t	height;

	if (!map || !filename)
		safe_exit(1, ERROR_MAP);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		safe_exit(1, ERROR_MAP);
	content = read_entire_file(fd);
	close(fd);
	if (!content)
		safe_exit(1, ERROR_ALLOCATION);
	height = count_lines(content);
	map->grid = split_into_grid(content, height);
	memory_free(content);
	if (!map->grid)
		safe_exit(1, ERROR_ALLOCATION);
	map->height = height;
	if (height > 0)
		map->width = ft_strlen(map->grid[0]);
	else
		map->width = 0;
}

void	check_shape(t_game *game_obj)
{
	size_t	i;

	if (!game_obj || !game_obj->map_obj)
		safe_exit(1, ERROR_MAP);
	i = 0;
	while (i < game_obj->map_obj->height)
	{
		if (ft_strlen(game_obj->map_obj->grid[i]) != game_obj->map_obj->width)
			safe_exit(1, ERROR_MAP);
		i++;
	}
	ft_putstr_fd("Map shape is valid.\n", 1);
}

static void	check_enclosed_by_walls(t_map *map)
{
	size_t	x;
	size_t	y;

	if (!map || !map->grid)
		safe_exit(1, ERROR_MAP);
	/* check top and bottom rows */
	x = 0;
	while (x < map->width)
	{
		if (map->grid[0][x] != '1' || map->grid[map->height - 1][x] != '1')
			safe_exit(1, ERROR_WALLS);
		x++;
	}
	/* check left and right columns */
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
	size_t	count_p;
	size_t	count_e;
	size_t	count_c;
	size_t	walls;

	if (!map || !map->grid)
		safe_exit(1, ERROR_MAP);
	count_p = 0;
	count_e = 0;
	count_c = 0;
	walls = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			char ch = map->grid[y][x];
			if (ch == 'P')
			{
				map->player_x = x;
				map->player_y = y;
				count_p++;
			}
			else if (ch == 'E')
				count_e++;
			else if (ch == 'C')
				count_c++;
			else if (ch == '1')
				walls++;
			else if (ch == '0')
			{
				/* free space */
			}
			else
				safe_exit(1, ERROR_CHARACTERS);
			x++;
		}
		y++;
	}
	map->collectibles = count_c;
	map->exit_pos = count_e;
	map->start_pos = count_p;
	map->wall_count = walls;
	if (count_p != 1)
		safe_exit(1, ERROR_PLAYER);
	if (count_e != 1)
		safe_exit(1, ERROR_EXIT);
	if (count_c < 1)
		safe_exit(1, ERROR_COLLECTIBLE);
}

static void	check_path_exists(t_map *map)
{
	size_t		cells;
	int		*visited;
	size_t		w;
	size_t		h;
	size_t		head;
	size_t		tail;
	size_t		*queue;
	size_t		start_idx;
	size_t		reachable_c;
	int		exit_found;

	w = map->width;
	h = map->height;
	cells = w * h;
	visited = memory_malloc(sizeof(int) * cells);
	if (!visited)
		safe_exit(1, ERROR_ALLOCATION);
	queue = memory_malloc(sizeof(size_t) * cells);
	if (!queue)
	{
		memory_free(visited);
		safe_exit(1, ERROR_ALLOCATION);
	}
	/* init visited */
	for (size_t i = 0; i < cells; i++)
		visited[i] = 0;
	/* start from player */
	start_idx = map->player_y * w + map->player_x;
	head = 0;
	tail = 0;
	queue[tail++] = start_idx;
	visited[start_idx] = 1;
	reachable_c = 0;
	exit_found = 0;
	while (head < tail)
	{
		size_t idx = queue[head++];
		size_t y = idx / w;
		size_t x = idx % w;
		char ch = map->grid[y][x];
		if (ch == 'C')
			reachable_c++;
		if (ch == 'E')
			exit_found = 1;
		/* explore neighbors: up/down/left/right if not wall and not visited */
		if (y > 0 && !visited[(y - 1) * w + x] && map->grid[y - 1][x] != '1')
		{
			visited[(y - 1) * w + x] = 1;
			queue[tail++] = (y - 1) * w + x;
		}
		if (y + 1 < h && !visited[(y + 1) * w + x] && map->grid[y + 1][x] != '1')
		{
			visited[(y + 1) * w + x] = 1;
			queue[tail++] = (y + 1) * w + x;
		}
		if (x > 0 && !visited[y * w + (x - 1)] && map->grid[y][x - 1] != '1')
		{
			visited[y * w + (x - 1)] = 1;
			queue[tail++] = y * w + (x - 1);
		}
		if (x + 1 < w && !visited[y * w + (x + 1)] && map->grid[y][x + 1] != '1')
		{
			visited[y * w + (x + 1)] = 1;
			queue[tail++] = y * w + (x + 1);
		}
	}
	memory_free(visited);
	memory_free(queue);
	if (reachable_c != map->collectibles || !exit_found)
		safe_exit(1, ERROR_MAP_PATH);
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