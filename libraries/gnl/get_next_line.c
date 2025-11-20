/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 23:15:00 by sdaban            #+#    #+#             */
/*   Updated: 2025/11/20 17:48:05 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include "../../src/allocation/allocation.h"

char	*cleanup_buffer(char *last)
{
	size_t	i;
	size_t	j;
	char	*p;

	if (!last)
		return (NULL);
	i = 0;
	while (last[i] != '\0' && last[i] != '\n')
		i++;
	if (last[i] == '\n')
		i++;
	if (last[i] == '\0')
		return (memory_free(last), NULL);
	p = memory_malloc(ft_strlen(last) - i + 1);
	if (!p)
		return (memory_free(last), NULL);
	j = 0;
	while (last[i])
		p[j++] = last[i++];
	p[j] = '\0';
	memory_free(last);
	return (p);
}

char	*read_until_newline(int fd, char *last)
{
	char	*buffer;
	char	*temp;
	ssize_t	len;

	buffer = memory_malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (memory_free(last), NULL);
	len = 1;
	while (!ft_strchr(last, '\n') && len != 0)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len < 0)
			return (memory_free(buffer), memory_free(last), NULL);
		buffer[len] = '\0';
		temp = ft_strjoin(last, buffer);
		memory_free(last);
		if (!temp)
			return (memory_free(buffer), NULL);
		last = temp;
	}
	memory_free(buffer);
	return (last);
}

char	*extract_line(char *last)
{
	size_t	i;
	size_t	j;
	char	*p;

	if (!last)
		return (NULL);
	i = 0;
	while (last[i] != '\0' && last[i] != '\n')
		i++;
	if (last[i] == '\n')
		i++;
	p = memory_malloc(i + 1);
	if (!p)
		return (NULL);
	j = 0;
	while (j < i)
	{
		p[j] = last[j];
		j++;
	}
	p[j] = '\0';
	return (p);
}

char	*get_next_line(int fd)
{
	static char	*last[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!last[fd])
	{
		last[fd] = memory_malloc(1);
		if (!last[fd])
			return (NULL);
		last[fd][0] = '\0';
	}
	last[fd] = read_until_newline(fd, last[fd]);
	if (!last[fd])
		return (NULL);
	if (!*last[fd])
		return ((memory_free(last[fd]), last[fd] = NULL), NULL);
	line = extract_line(last[fd]);
	if (!line)
		return ((memory_free(last[fd]), last[fd] = NULL), NULL);
	last[fd] = cleanup_buffer(last[fd]);
	return (line);
}
