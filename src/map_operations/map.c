/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:17:14 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/20 17:50:43 by sdaban           ###   ########.fr       */
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
}