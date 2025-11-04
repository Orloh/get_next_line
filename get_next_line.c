/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhernan <ohercelli@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:41:41 by orhernan          #+#    #+#             */
/*   Updated: 2025/11/03 23:32:46 by orhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_from_file(int fd)
{
	char	*buffer;
	size_t	bytes_read;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (free (buffer), NULL);
	return (buffer);
}

char	*read_next_line(int fd)
{
	char	*buffer;

	buffer = read_from_file(fd);
	if (!buffer)
		return (NULL);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!store)
	{
		store = ft_calloc(1, sizeof(char));
		if (!store)
			return (NULL);
	}
	while (1)
	{
		line = ft_strchr(store,'\n');
		if (line)
		{
			*line = '\0';
			buffer = store;
			store = ft_strdup(line + 1);
			return(buffer);
		}
		buffer = read_from_file(fd);
		if (!buffer)
		{
			line = store;
			store = NULL;
			if (line && *line)
				return (line);
			free (line);
			return (NULL);
		}
		line = ft_strjoin(store, buffer);
		free (buffer);
		free (store);
		store = line;
		if (!store)
			return (NULL);
	}
}
