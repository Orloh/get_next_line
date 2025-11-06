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

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store = ft_read_from_file(fd, store);
	if (!store)
		return (NULL);
	line = ft_get_line(store);
	store = ft_get_rest(store);
	return (line);
}

char	*ft_read_from_file(int fd, char *store)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	if (!store)
		store = ft_strdup("");
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free (buffer), NULL);
		buffer[bytes_read] = 0;
		temp = store;
		store = ft_strjoin(store, buffer);
		free(temp);
	}
	return (store);
}

char	*ft_get_line(char *store)
{
	size_t	l_len;
	char	*line;

	l_len = 0;
	if (!store[0])
		return (NULL);
	while (store[l_len] && store[l_len] != '\n')
		l_len++;
	line = ft_substr(store, 0, l_len + 1);
	if (!line || !*line)
		return (NULL);
	return (line);
}

char	*ft_get_rest(char *store)
{
	size_t	l_len;
	char	*rest;

	l_len = 0;
	while (store[l_len] && store[l_len] != '\n')
		l_len++;
	if (!store[l_len])
		return (free(store), NULL);
	rest = ft_substr(store, l_len + 1, ft_strlen(store));
	if (!rest || !*rest)
		return (NULL);
	return (free(store), rest);
}
