/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_extract_next_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhernan <ohercelli@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:55:44 by orhernan          #+#    #+#             */
/*   Updated: 2025/11/04 14:01:25 by orhernan         ###   ########.fr       */
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
	char	*buffer = "Line1\nLine2\n";
	char	*result = extract_new_line(buffer);

	TEST_ASSERT_NOT_NULL(result);
	TEST_ASSERT_EQUAL_STRING("Line1\n", result);

	free (result);
}

void	test_extract_empty_buffer(void)
{
	char	*buffer = "";
	char	*result = extract_new_line(buffer);

	TEST_ASSERT_NULL(result);
}

void	test_extract_end_of_line(void)
{
	char	*buffer = "Line3";
	char	*result = extract_new_line(buffer);

	TEST_ASSERT_NOT_NULL(result);
	TEST_ASSERT_EQUAL_STRING("Line3", result);
}

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_extract_nl);
	RUN_TEST(test_extract_empty_buffer);
	RUN_TEST(test_extract_end_of_line);
	return UNITY_END();
}
