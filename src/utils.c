/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:49:00 by sdaban            #+#    #+#             */
/*   Updated: 2025/03/06 12:09:28 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../vendor/libft/libft.h"

int	compare_2_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (0);
	}
	return (1);
}

int	is_collectible(t_game *game)
{
	return (game->map->temp_map[game->map->player_line]
		[game->map->player_col] == 'C');
}

void	set_player_position(t_map *map, int l, int c)
{
	map->player_line = l;
	map->player_col = c;
}

void	print_move_count(int count)
{
	ft_putstr_fd("Player Move Count: ", 1);
	ft_putnbr_fd(count, 1);
	ft_putchar_fd('\n', 1);
}
