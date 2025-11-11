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
void	test_read_multiple_fd(void)
{
	int fd1 = create_temp_file("line1\nline2\nline3\n");
	int fd2 = create_temp_file("a1\na2\n");
	int fd3 = create_temp_file("Esto es una prueba para saber si lei el texto\n esta es la segunda linea\nesta es la ultima");

	TEST_ASSERT_NOT_EQUAL(-1, fd1);
	TEST_ASSERT_NOT_EQUAL(-1, fd2);
	TEST_ASSERT_NOT_EQUAL(-1, fd3);
	

	char *f1l1 = get_next_line(fd1);
	char *f2l1 = get_next_line(fd2);
	char *f3l1 = get_next_line(fd3);
	char *f1l2 = get_next_line(fd1);
	char *f2l2 = get_next_line(fd2);
	char *f3l2 = get_next_line(fd3);
	char *f1l3 = get_next_line(fd1);
	char *f2l3 = get_next_line(fd2);
	char *f3l3 = get_next_line(fd3);
	char *f1l4 = get_next_line(fd1);
	char *f3l4 = get_next_line(fd3);

	TEST_ASSERT_EQUAL_STRING("line1\n", f1l1);
	TEST_ASSERT_EQUAL_STRING("line2\n", f1l2);
	TEST_ASSERT_EQUAL_STRING("line3\n", f1l3);
	TEST_ASSERT_NULL(f1l4);
	
	TEST_ASSERT_EQUAL_STRING("a1\n", f2l1);
	TEST_ASSERT_EQUAL_STRING("a2\n", f2l2);
	TEST_ASSERT_NULL(f2l3);
	
	TEST_ASSERT_EQUAL_STRING("Esto es una prueba para saber si lei el texto\n", f3l1);
	TEST_ASSERT_EQUAL_STRING(" esta es la segunda linea\n", f3l2);
	TEST_ASSERT_EQUAL_STRING("esta es la ultima", f3l3);
	TEST_ASSERT_NULL(f3l4);

	free(f1l1);
	free(f1l2);
	free(f1l3);
	free(f2l1);
	free(f2l2);
	free(f3l1);
	free(f3l2);
	free(f3l3);
	close(fd1);
	close(fd2);
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
	RUN_TEST(test_read_multiple_fd);
	return UNITY_END();
}
