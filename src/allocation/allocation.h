/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:34:09 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/22 13:06:42 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATION_H
# define ALLOCATION_H

# include <stddef.h>
# include "../../include/so_long.h"

typedef struct s_memory
{
	void			*ptr;
	struct s_memory	*next;
}					t_memory;

void				*memory_malloc(size_t size);
void				memory_free(void *ptr);
void				memory_cleanup(int status);
void				safe_exit(int return_code, const char *error_msg);
void				finish_and_clean(t_game *game);
#endif