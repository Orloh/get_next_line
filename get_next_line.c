/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhernan <ohercelli@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:41:41 by orhernan          #+#    #+#             */
/*   Updated: 2025/10/27 19:03:24 by orhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char *	buffer[100];
	size_t	bytes_read;

	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read == -1)
		return ();
	write(1, buffer, bytes_read);
	return (buffer);
}
