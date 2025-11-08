/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_read_from_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhernan <ohercelli@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 23:11:53 by orhernan          #+#    #+#             */
/*   Updated: 2025/11/06 00:41:19 by orhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include "unity.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= strlen(s))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
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

// Read from empty file
void	test_read_empty_file(void)
{
	int	fd = create_temp_file("");
	TEST_ASSERT_NOT_EQUAL(-1, fd);

	char	*result = NULL;
	result = ft_read_from_file(fd, result);
	TEST_ASSERT_NOT_NULL(result);
	TEST_ASSERT_EQUAL_STRING("", result);

	close(fd);
}

// Read one line
void	test_read_single_line(void)
{
	int	fd = create_temp_file("Hello World\n");
	TEST_ASSERT_NOT_EQUAL(-1, fd);

	char	*result = NULL ;
	result = ft_read_from_file(fd, result);
	TEST_ASSERT_NOT_NULL(result);
	TEST_ASSERT_EQUAL_STRING("Hello World\n", result);

	free(result);
	close(fd);
}

// Read long line
void test_read_long_line(void)
{
	const char	*chunk = "ABCDE";
	const size_t	chunks_per_read = (BUFFER_SIZE / 5) + 1;
	const size_t	total_chunks = chunks_per_read + 1;
	const size_t	line_len = total_chunks * 5;

	char	*expected_line = ft_calloc(line_len + 2, 1);
	TEST_ASSERT_NOT_NULL(expected_line);

	for (size_t i = 0; i < total_chunks; ++i)
		memcpy(expected_line + i*5, chunk, 5);
	expected_line[line_len] = '\n';
	expected_line[line_len + 1] = '\0';

	int	fd = create_temp_file(expected_line);
	TEST_ASSERT_NOT_EQUAL(-1, fd);

	char	*result = NULL ;
	result = ft_read_from_file(fd, result);
	TEST_ASSERT_NOT_NULL(result);
	TEST_ASSERT_EQUAL_STRING(expected_line, result);

	free(expected_line);
	free(result);
	close(fd);
}

void	test_read_multiple_lines(void)
{
	const char	*file_content = "Line1\nLine2\nLine3";
	const size_t	file_len = ft_strlen(file_content);
	
	int	fd = create_temp_file(file_content);
	TEST_ASSERT_NOT_EQUAL(-1, fd);

	size_t	file_offset = 0;

	while (file_offset < file_len)
	{
		char	*result = NULL;
		result = ft_read_from_file(fd, result);
		TEST_ASSERT_NOT_NULL(result);
		
		size_t remaining = file_len - file_offset;
		size_t expected_len = (remaining < BUFFER_SIZE) ? remaining : BUFFER_SIZE;

		const char	*expected_line = ft_substr(file_content, file_offset, expected_len);
		TEST_ASSERT_EQUAL_STRING(expected_line, result);
		TEST_ASSERT_EQUAL_CHAR('\0', result[expected_len]);
		TEST_ASSERT_EQUAL_INT(expected_len, ft_strlen(result));
		free (result);
		file_offset += expected_len;
	}

	char	*eof_result = NULL;
	eof_result = ft_read_from_file(fd, eof_result);
	TEST_ASSERT_NOT_NULL(eof_result);
	TEST_ASSERT_EQUAL_STRING("", eof_result);
	close (fd);
}

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_read_empty_file);
	RUN_TEST(test_read_single_line);
	RUN_TEST(test_read_long_line);
	RUN_TEST(test_read_multiple_lines);
	return UNITY_END();
}
