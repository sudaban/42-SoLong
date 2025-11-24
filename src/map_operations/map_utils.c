/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:12:15 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/24 10:46:20 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "../../include/so_long.h"
#include "../../libraries/gnl/get_next_line.h"
#include "../../libraries/libft/libft.h"
#include "../allocation/allocation.h"
#include "map.h"

void	free_grid(char **g, size_t h)
{
	size_t	i;

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

size_t	count_lines(const char *str)
{
	size_t	count;
	size_t	i;

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

void	free_grid_partial(char **copy, size_t filled)
{
	size_t	i;

	i = 0;
	while (i < filled)
	{
		memory_free(copy[i]);
		i++;
	}
	memory_free(copy);
}

char	*append_line(char *content, char *line)
{
	char	*temp;
	size_t	len;

	if (!content)
	{
		len = ft_strlen(line);
		content = memory_malloc(len + 1);
		if (!content)
			return (NULL);
		ft_memcpy(content, line, len + 1);
		return (content);
	}
	temp = ft_strjoin(content, line);
	memory_free(content);
	if (!temp)
		return (NULL);
	return (temp);
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
