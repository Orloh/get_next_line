/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_get_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhernan <ohercelli@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:55:44 by orhernan          #+#    #+#             */
/*   Updated: 2025/11/06 13:00:08 by orhernan         ###   ########.fr       */
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

void	test_extract_nl(void)
{
	char	*content = "Line1\nLine2\nLine3\n";
	char	*buffer = ft_strdup(content);
	char	*result = ft_get_line(buffer);

	TEST_ASSERT_NOT_NULL(result);
	TEST_ASSERT_EQUAL_STRING("Line1\n", result);

	free (result);
}

void	test_extract_empty_buffer(void)
{
	char	*content = "";
	char	*buffer = ft_strdup(content);
	char	*result = ft_get_line(buffer);

	TEST_ASSERT_NULL(result);
}

void	test_extract_end_of_line(void)
{
	char	*content = "Line1";
	char	*buffer = ft_strdup(content);
	char	*result = ft_get_line(buffer);

	TEST_ASSERT_NOT_NULL(result);
	TEST_ASSERT_EQUAL_STRING("Line1", result);
}

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_extract_nl);
	RUN_TEST(test_extract_empty_buffer);
	RUN_TEST(test_extract_end_of_line);
	return UNITY_END();
}
