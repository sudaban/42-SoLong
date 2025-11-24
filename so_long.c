/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:21:55 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/24 11:07:51 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include "include/so_long.h"
#include "libraries/libft/libft.h"
#include "src/allocation/allocation.h"
#include "libraries/mlx/mlx.h"

static t_game	*setup_game(char *filename)
{
	t_game	*god_obj;

	check_file_name(filename);
	god_obj = init_game();
	if (!god_obj)
		safe_exit(1, ERROR_ALLOCATION);
	god_obj->map_obj = init_map();
	if (!god_obj->map_obj)
		safe_exit(1, ERROR_ALLOCATION);
	load_map_data(god_obj->map_obj, filename);
	check_shape(god_obj);
	validate_map(god_obj->map_obj);
	god_obj->res_obj = init_resources();
	init_mlx(god_obj);
	set_textures(god_obj);
	render_resources(god_obj);
	return (god_obj);
}

int	main(int argc, char **argv)
{
	t_game	*god_obj;
	char	*filename;

	if (argc != 2)
	{
		ft_putstr_fd(ERROR_ARGC, 2);
		return (1);
	}
	filename = argv[1];
	god_obj = setup_game(filename);
	mlx_hook(god_obj->res_obj->window, KeyPress, KeyPressMask,
		handle_key_press, god_obj);
	mlx_hook(god_obj->res_obj->window, 17, 1 << 17L,
		handle_close, god_obj);
	mlx_loop(god_obj->mlx_obj);
	return (0);
}
