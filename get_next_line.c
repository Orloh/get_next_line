/* ************************************************************************** */ /*                                                                            */
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

char	*get_next_line(int fd)
{
	char	*buffer;
	static char 	*store;
	size_t	bytes_read;

	printf("ft_calloc[%d]--->", count++);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free (buffer);
		return (NULL);
	}
	if (!store)
	{
		store = ft_calloc(1, sizeof(char));
		if (!store)
			return (NULL);
	}
	while (/*if buffer does not have the new line char*/)
	{
		/*append buffer to store*/
		store = ft_strjoin(store, buffer);
	}
	return (buffer);
}
