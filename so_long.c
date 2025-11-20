/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:21:55 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/20 17:08:42 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "include/so_long.h"
#include "libraries/libft/libft.h"
#include "src/allocation/allocation.h"

int	main(int argc, char **argv)
{
	t_game	*god_obj;
	char*	filename;
	if (argc != 2)
	{
		ft_putstr_fd(ERROR_ARGC, 2);
		return (1);
	}
	else
	{
		filename = argv[1];
		check_file_name(filename);
		god_obj = init_game();
		if (!god_obj)
			safe_exit(1, ERROR_ALLOCATION);
		god_obj->map_obj = init_map();
		if (!god_obj->map_obj)
			safe_exit(1, ERROR_ALLOCATION);
		load_map_data(god_obj->map_obj, filename);
		memory_cleanup(0);
	}
	return (0);
}
