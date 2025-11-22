/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:17:14 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/22 15:08:32 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
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
				continue ;
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

static char	**dup_grid(char **grid, size_t height, size_t width)
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
			size_t j = 0;
			while (j < i)
			{
				memory_free(copy[j]);
				j++;
			}
			memory_free(copy);
			return (NULL);
		}
		ft_memcpy(copy[i], grid[i], width);
		copy[i][width] = '\0';
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	free_grid(char **g, size_t h)
{
	size_t i;

	if (!g)
		return ;
	i = 0;
	while (i < h)
	{
		if (g[i])
			memory_free(g[i]);
		i++;
	}
	memory_free(g);
}

static void	dfs(char **str, int *elements, int x, int y, size_t h, size_t w)
{
	if (x < 0 || y < 0)
		return ;
	if ((size_t)x >= h || (size_t)y >= w)
		return ;
	if (str[x][y] == '1' || *elements == 0)
		return ;
	if (str[x][y] == 'E' || str[x][y] == 'C')
		(*elements)--;
	str[x][y] = '1';
	dfs(str, elements, x, y + 1, h, w);
	dfs(str, elements, x, y - 1, h, w);
	dfs(str, elements, x + 1, y, h, w);
	dfs(str, elements, x - 1, y, h, w);
}

static void	check_path_exists(t_map *map)
{
	char	**copy;
	int		elements;

	if (!map || !map->grid)
		safe_exit(1, ERROR_MAP);
	copy = dup_grid(map->grid, map->height, map->width);
	if (!copy)
		safe_exit(1, ERROR_ALLOCATION);
	elements = (int)map->collectibles + (int)map->exit_pos;
	dfs(copy, &elements, (int)map->player_y, (int)map->player_x,
		map->height, map->width);
	free_grid(copy, map->height);
	if (elements != 0)
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
