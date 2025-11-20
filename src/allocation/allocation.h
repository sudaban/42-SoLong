/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:34:09 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/20 10:35:21 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATION_H
# define ALLOCATION_H

# include <stddef.h>

typedef struct s_memory
{
	void			*ptr;
	struct s_memory	*next;
}					t_memory;

void				*memory_malloc(size_t size);
void				memory_free(void *ptr);
void				memory_cleanup(int status);
#endif