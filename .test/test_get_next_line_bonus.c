/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_next_line_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhernan <ohercelli@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:39:03 by orhernan          #+#    #+#             */
/*   Updated: 2025/11/08 17:44:54 by orhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void	setUp(void) {}
void	tearDown(void) {}

// Create temp file
static int	create_temp_file(const char *content)
{
	char	 template[] = "/tmp/testfile.XXXXXX";
	int	fd = mkstemp(template);
	
	if (fd == -1) TEST_FAIL_MESSAGE("mkstemp failed");
	if (!content && write (fd, content, ft_strlen(content)) == -1)
	{
		close (fd);
		TEST_FAIL_MESSAGE("write failed");
	}
	lseek(fd, 0, SEEK_SET);
	unlink(template);
	return fd;
}v

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
