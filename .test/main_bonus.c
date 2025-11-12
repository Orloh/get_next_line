/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhernan <ohercelli@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:19:01 by orhernan          #+#    #+#             */
/*   Updated: 2025/11/12 11:26:51 by orhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;

	fd1 = open("file1.txt", O_RDONLY);
	if (fd1 == -1)
	{
		printf("Could not open the file.\n");
		return (1);
	}
	fd2 = open("file2.txt", O_RDONLY);
	if (fd 2 == -1)
	{
		close(fd1);
		printf("Coulld not open the file.\n);
	 	return (1);
	}
	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		if (!line1 && !line2)
			break ;
		printf("\nl1\t%s", line1);
		printf("\nl2\t%s", line2);
		free(line1);
		free(line2);
		line1 = NULL;
		line2 = NULL;
	}
	close (fd1);
	close (fd2);
	return (0);
}
