/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_next_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhernan <ohercelli@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 23:51:42 by orhernan          #+#    #+#             */
/*   Updated: 2025/11/06 01:01:45 by orhernan         ###   ########.fr       */
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

// Read from an empty file
void	test_read_empty_file(void)
{
	int	fd = create_temp_file("");
	TEST_ASSERT_NOT_EQUAL(-1, fd);
	
	char	*line = get_next_line(fd);
	TEST_ASSERT_NULL(line);

	close(fd);
}

void	test_read_only_nl(void)
{
	int	fd = create_temp_file("\n");
	TEST_ASSERT_NOT_EQUAL(-1, fd);
	
	char	*line = get_next_line(fd);
	TEST_ASSERT_NOT_NULL(line);
	TEST_ASSERT_EQUAL_STRING("\n", line);
	free(line);

	line = get_next_line(fd);
	TEST_ASSERT_NULL(line);

	close(fd);
}

void	test_read_line_with_no_nl(void)
{
	int	fd = create_temp_file("Hello World!");
	TEST_ASSERT_NOT_EQUAL(-1, fd);

	char	*line = get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING("Hello World!", line);
	free(line);

	line = get_next_line(fd);
	TEST_ASSERT_NULL(line);

	close(fd);
}

void	test_read_line_with_nl(void)
{
	int	fd = create_temp_file("Hello World!\n");
	TEST_ASSERT_NOT_EQUAL(-1, fd);

	char	*line = get_next_line(fd);
	TEST_ASSERT_EQUAL_STRING("Hello World!\n", line);
	free(line);

	line = get_next_line(fd);
	TEST_ASSERT_NULL(line);

	close(fd);
}

void	test_invalid_fd(void)
{
    char	*line = get_next_line(-1);
    TEST_ASSERT_NULL(line);
}

void	test_read_error(void)
{
    // Create a file, then close and try to read
    int		fd = create_temp_file("error");
    close(fd);
    char	*line = get_next_line(fd);
    TEST_ASSERT_NULL(line);
}

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_read_empty_file);
	RUN_TEST(test_read_only_nl);
	RUN_TEST(test_read_line_with_no_nl);
	RUN_TEST(test_read_line_with_nl);
	RUN_TEST(test_invalid_fd);
	RUN_TEST(test_read_error);
	return UNITY_END();
}
