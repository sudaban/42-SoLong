/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:11:40 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/22 17:10:58 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include <stddef.h>
# include "../../include/so_long.h"

typedef struct s_flood
{
	char	**grid;
	size_t	height;
	size_t	width;
	int		*elements;
}	t_flood;

void	free_grid(char **g, size_t h);
size_t	count_lines(const char *str);
void	free_grid_partial(char **copy, size_t filled);
char	*append_line(char *content, char *line);
void	_process_char(t_map *map, size_t x, size_t y, size_t counts[3]);
void	_check_map_counts(t_map *map);
int		_process_grid_lines(char **grid, const char *content);
void	load_map_data(t_map *map, const char *filename);
char	**split_into_grid(const char *content, size_t height);
void	check_path_exists(t_map *map);
char	*read_entire_file(int fd);
char	**dup_grid(char **grid, size_t height, size_t width);
#endif