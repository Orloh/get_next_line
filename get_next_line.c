/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhernan <ohercelli@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:41:41 by orhernan          #+#    #+#             */
/*   Updated: 2025/10/29 11:55:01 by orhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_from_file(int fd)
{
	char	*buffer;
	size_t	bytes_read;
	static int		count;

	if (!count)
		count = 0;
	printf("ft_calloc[%d]--->", count++);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (free (buffer), NULL);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*buffer;
	char		*aux;
	char		*rest;

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
		buffer = read_from_file(fd);
		if (!buffer && !store)
			return (NULL);
		aux = store;
		store = ft_strjoin(store, buffer);
		if (!store)
			return (free(buffer), NULL);
		free(aux);
		aux = NULL;
		rest = ft_strchr(store,'\n');
		if (rest)
		{
			*rest = '\0';
			aux = store;
			store = ft_strdup(rest + 1);
			return(aux);
		}
		if (!rest && store)
		{
			aux = store;
			store = NULL;
			return(aux);
		}
	}
	return (free(aux), store);
}
