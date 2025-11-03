/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_read_from_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhernan <ohercelli@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:03:22 by orhernan          #+#    #+#             */
/*   Updated: 2025/11/03 23:02:44 by orhernan         ###   ########.fr       */
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

// Normal Read
void	test_read_normal(void)
{
	const char	*input = "Hello";
	int	fd = create_temp_file(input);
	TEST_ASSERT_NOT_EQUAL(-1, fd);
	
	char	*result = read_from_file(fd);
	TEST_ASSERT_NOT_NULL(result);
	
	size_t	to_read = BUFFER_SIZE < 5 ? BUFFER_SIZE : 5;
	TEST_ASSERT_EQUAL_MEMORY(input, result, to_read);
	TEST_ASSERT_EQUAL_CHAR('\0', result[BUFFER_SIZE]);

	free(result);
	close(fd);
}

// Full buffer (BUFFER_SIZE bytes)
void	test_read_full_buffer(void)
{
	char	content[BUFFER_SIZE];
	memset(content, 'A', BUFFER_SIZE);
	content[BUFFER_SIZE] = '\0';

	int	fd = create_temp_file(content);
	TEST_ASSERT_NOT_EQUAL(-1, fd);

	char	*result = read_from_file(fd);
	TEST_ASSERT_NOT_NULL(result);
	TEST_ASSERT_EQUAL_MEMORY(content, result, BUFFER_SIZE);
	TEST_ASSERT_EQUAL_CHAR('\0', result[BUFFER_SIZE]);

	free(result);
	close(fd);
}

// Empty file
void	test_read_empty_file(void)
{
	int	fd = create_temp_file("");
	TEST_ASSERT_NOT_EQUAL(-1, fd);

	char	*result = read_from_file(fd);
	TEST_ASSERT_NULL(result);

	close(fd);
}

// read() error
void	test_read_error(void)
{
	char	*result = read_from_file(-1);
	TEST_ASSERT_NULL(result);
}

// Multiple reads from same file
void	test_multiple_reads(void)
{
	const char	*chunk = "ABCDE";
	const size_t	chunk_len = ft_strlen(chunk);
	const size_t	chunks_needed = (BUFFER_SIZE / chunk_len) + 2;
	const size_t	total_len = chunks_needed * chunk_len;

	char	*file_content = ft_calloc(total_len + 1, sizeof(char));
	TEST_ASSERT_NOT_NULL(file_content);
	for (size_t i = 0; i < chunks_needed; ++i)
		memcpy(file_content + i * chunk_len, chunk, chunk_len);

	int	fd = create_temp_file(file_content);
	TEST_ASSERT_NOT_EQUAL(-1, fd);
	
	size_t offset = 0;
	sisize_tt read_count = 0;

	while (1)
	{
		char	*buffer = read_from_file(fd);
		read_count++;

		if (!buffer)
		{
			TEST_ASSERT_EQUAL(total_len, offset);
			break;
		}

		TEST_ASSERT_NOT_NULL(buffer);

		size_t	expected_len = total_len - offset;
		if (expected_len > BUFFER_SIZE)
			expected_len = BUFFER_SIZE;

		TEST_ASSERT_EQUAL_MEMORY(file_content + offset, buffer, expected_len);
		TEST_ASSERT_EQUAL_CHAR('\0', buffer[BUFFER_SIZE]);
		TEST_ASSERT_EQUAL_INT(expected_len, ft_strlen(buffer));

		free(buffer);
		offset += expected_len;
	}

	close(fd);
	free(file_content);

	size_t	min_reads = (total_len + BUFFER_SIZE -1) / BUFFER_SIZE;
	TEST_ASSERT_TRUE(read_count >= min_reads);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_read_normal);
	RUN_TEST(test_read_full_buffer);
	RUN_TEST(test_read_empty_file);
	RUN_TEST(test_read_error);
	RUN_TEST(test_multiple_reads);
	return UNITY_END();
}
