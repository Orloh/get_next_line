/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhernan <orhernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:41:41 by orhernan          #+#    #+#             */
/*   Updated: 2025/11/06 12:59:59 by orhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*store[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store[fd] = ft_read_from_file(fd, store[fd]);
	if (!store[fd])
		return (NULL);
	line = ft_get_line(store[fd]);
	store[fd] = ft_get_rest(store[fd]);
	return (line);
}

char	*ft_read_from_file(int fd, char *store)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	if (!store)
		store = ft_calloc(1, 1);
	if (!store)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(store), NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free (buffer), free(store), NULL);
		buffer[bytes_read] = 0;
		temp = store;
		store = ft_strjoin(store, buffer);
		free(temp);
		if (!store)
			return (free(buffer), NULL);
	}
	return (free(buffer), store);
}

char	*ft_get_line(char *store)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	if (!store || !store[0])
		return (NULL);
	while (store[i] && (store)[i] != '\n')
		i++;
	line = ft_calloc(i + (store[i] == '\n') + 1, sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = store[j];
		j++;
	}
	if (store[i] == '\n')
		line[j++] = '\n';
	return (line);
}

char	*ft_get_rest(char *store)
{
	size_t	i;
	size_t	j;
	char	*rest;

	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	if (!store[i])
		return (free(store), NULL);
	rest = ft_calloc((ft_strlen(store) - i) + 1, sizeof(char));
	i++;
	j = 0;
	while (store[i])
		rest[j++] = store[i++];
	return (free(store), rest);
}
