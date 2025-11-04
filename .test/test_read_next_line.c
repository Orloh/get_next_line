/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_read_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhernan <ohercelli@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 23:11:53 by orhernan          #+#    #+#             */
/*   Updated: 2025/11/03 23:32:41 by orhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include "unity.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void	setUp(void) {}
void	tearDown(void) {}

// Create temp file
static int	create_temp_file(const char *content)
{
	char	 template[] = "/tmp/testfile.XXXXXX";
	int	fd = mkstemp(template);
	
	if (fd == -1) return (-1);
	if (content)
		write (fd, content, ft_strlen(content));
	lseek(fd, 0, SEEK_SET);
	unlink(template);
	return fd;
}

void	test_read_empty_file(void)
{
	int	fd = create_temp_file("");
	TEST_ASSERT_NOT_EQUAL(-1, fd);

	char	*result = read_next_line(fd);
	TEST_ASSERT_NULL(result);

	close(fd);
}

void	test_

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_read_empty_file);
	return UNITY_END();
}
