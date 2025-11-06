/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhernan <orhernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:41:41 by orhernan          #+#    #+#             */
/*   Updated: 2025/11/06 01:09:43 by orhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char		*substring;
	size_t		str_len;
	size_t		i;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if (str_len - start < len)
		len = str_len - start;
	substring = ft_calloc(len + 1, sizeof(char));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	return (substring);
}

char	*read_from_file(int fd)
{
	char	*buffer;
	ssize_t	bytes_read;

	if (fd < 0)
		return (NULL);
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
	char	*line;
	char	*temp;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (!ft_strchr(line, '\n'))
	{
		buffer = read_from_file(fd);
		if (!buffer)
		{
			if (*line)
				return (line);
			else
				return (free(line), NULL);
		}
		temp = line;
		line = ft_strjoin(line, buffer);
		free(temp);
		free(buffer);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*extract_new_line(const char *buffer)
{
	size_t	len;
	char	*new_line;

	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	new_line = ft_substr(buffer, 0, len + 1);
	if (!new_line || !*new_line)
		return (NULL);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*buffer;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!store)
		store = ft_calloc(1, sizeof(char));
	if (!store)
		return (NULL);
	buffer = read_next_line(fd);
	if (!buffer && !*store)
		return (free(store), store = NULL, NULL);
	temp = store;
	store = ft_strjoin(store, buffer);
	free(temp);
	if (buffer)
		free(buffer);
	line = extract_new_line(store);
	if (!line)
		return (free(store), store = NULL, NULL);
	temp = store;
	if (ft_strchr(store, '\n'))
		store = ft_strdup(ft_strchr(store, '\n') + 1);
	else
		store = NULL;
	return (free(temp), line);
}
