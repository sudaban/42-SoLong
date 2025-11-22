/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:26:13 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/22 13:02:53 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocation.h"
#include <unistd.h>

void	safe_exit(int return_code, const char *error_msg)
{
	size_t	len;

	len = 0;
	while (error_msg && error_msg[len])
		len++;
	if (error_msg)
	{
		write(2, error_msg, len);
		write(2, "\n", 1);
	}
	memory_cleanup(return_code);
}
