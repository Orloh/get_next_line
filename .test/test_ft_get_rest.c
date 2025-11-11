/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_get_rest.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhernan <ohercelli@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:13:00 by orhernan          #+#    #+#             */
/*   Updated: 2025/11/06 13:00:01 by orhernan         ###   ########.fr       */
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

void	test_extract_rest_nl(void)
{
	char	*content = "Line1\nLine2\nLine3\n";
	char	*buffer = ft_strdup(content);
	char	*result = ft_get_rest(buffer);

	TEST_ASSERT_NOT_NULL(result);
	TEST_ASSERT_EQUAL_STRING("Line2\nLine3\n", result);

	free (result);
}

void	test_extract_rest_no_nl(void)
{
	char	*content = "Line1\nLine2\nLine3";
	char	*buffer = ft_strdup(content);
	char	*result = ft_get_rest(buffer);

	TEST_ASSERT_NOT_NULL(result);
	TEST_ASSERT_EQUAL_STRING("Line2\nLine3", result);

	free(result);
}

void	test_extract_empty_buffer(void)
{
	char	*buffer = ft_strdup("");
	char	*result = ft_get_rest(buffer);

	TEST_ASSERT_NULL(result);
}

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_extract_rest_nl);
	RUN_TEST(test_extract_rest_no_nl);
	RUN_TEST(test_extract_empty_buffer);
	return UNITY_END();
}
