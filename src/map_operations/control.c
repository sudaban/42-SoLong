/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:17:16 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/24 10:35:55 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../../include/so_long.h"
#include "../allocation/allocation.h"
#include "../../libraries/libft/libft.h"

void	check_file_name(const char *filename)
{
	size_t	len;
	int		fd;

	if (!filename)
		safe_exit(1, ERROR_MAP);
	len = 0;
	while (filename[len] != '\0')
		len++;
	if (len < 5 || filename[len - 1] != 'r' || filename[len - 2] != 'e'
		|| filename[len - 3] != 'b' || filename[len - 4] != '.')
		safe_exit(1, ERROR_EXTENSION);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		safe_exit(1, ERROR_MAP);
	if (close(fd) < 0)
		safe_exit(1, ERROR_MAP);
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
