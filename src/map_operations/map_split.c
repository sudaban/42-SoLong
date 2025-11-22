/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:27:30 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/22 17:11:09 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "../allocation/allocation.h"
#include "../../libraries/libft/libft.h"

static char	*_create_and_copy_row(const char *content, size_t start, size_t len)
{
	char	*row;

	row = memory_malloc(len + 1);
	if (!row)
		return (NULL);
	ft_memcpy(row, &content[start], len);
	row[len] = '\0';
	return (row);
}

int	_process_grid_lines(char **grid, const char *content)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	start = 0;
	while (content[i])
	{
		if (content[i++] == '\n')
		{
			grid[j] = _create_and_copy_row(content, start, (i - 1) - start);
			if (!grid[j++])
				return (0);
			start = i;
		}
	}
	if (start < i)
	{
		grid[j] = _create_and_copy_row(content, start, i - start);
		if (!grid[j++])
			return (0);
	}
	grid[j] = NULL;
	return (1);
}

char	**split_into_grid(const char *content, size_t height)
{
	char	**grid;

	if (!content)
		return (NULL);
	grid = memory_malloc(sizeof(char *) * (height + 1));
	if (!grid)
		return (NULL);
	if (!_process_grid_lines(grid, content))
		return (NULL);
	return (grid);
}
