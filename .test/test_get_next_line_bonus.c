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
	int	w = 0;
	TEST_ASSERT_NOT_EQUAL(-1,fd);
	
	if (content) 
		w = write (fd, content, ft_strlen(content));
	if (w == -1)
	{
		TEST_FAIL_MESSAGE("write failed");
		close(fd);
	}
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

// Get line with only one new line char
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

// get line with no new line char
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

// get line with new line char
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

// read from invalid file descriptor
void	test_invalid_fd(void)
{
    char	*line = get_next_line(-1);
    TEST_ASSERT_NULL(line);
}

// read from closed file descriptor
void	test_read_error(void)
{
    // Create a file, then close and try to read
    int		fd = create_temp_file("error");
    close(fd);
    char	*line = get_next_line(fd);
    TEST_ASSERT_NULL(line);
}

// read from multiple files
void	test_read_multiple_lines(void)
{
	int fd = create_temp_file("line1\nline2\nline3\n");
	TEST_ASSERT_NOT_EQUAL(-1, fd);

	char *l1 = get_next_line(fd);
	char *l2 = get_next_line(fd);
	char *l3 = get_next_line(fd);
	char *l4 = get_next_line(fd);

	TEST_ASSERT_EQUAL_STRING("line1\n", l1);
	TEST_ASSERT_EQUAL_STRING("line1\n", l1);
	TEST_ASSERT_EQUAL_STRING("line1\n", l1);
	TEST_ASSERT_NULL(l4);
	
	free(l1);
	free(l2);
	free(l3);
	close(fd);
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
	RUN_TEST(test_read_multiple_lines);
	return UNITY_END();
}
