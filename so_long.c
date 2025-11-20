/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:21:55 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/20 11:50:07 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "include/so_long.h"
#include "libraries/libft/libft.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd(ERROR_ARGC, 2);
		return (1);
	}
	else
	{
		check_file_name(argv[1]);
		return (0);
	}
	return (0);
}
