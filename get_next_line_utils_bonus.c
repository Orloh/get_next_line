/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhernan <orhernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:05:07 by orhernan          #+#    #+#             */
/*   Updated: 2025/11/06 12:38:08 by orhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*ptr;
	size_t		total;
	char		*p;

	if (size == 0 || count == 0)
		return (malloc(0));
	total = count * size;
	if (total / count != size)
		return (NULL);
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	p = (char *)ptr;
	while (total--)
		p[total] = '\0';
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	str_len;
	char	*original;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	str_len = ft_strlen(s1) + ft_strlen(s2);
	original = ft_calloc(str_len + 1, sizeof(char));
	if (!original)
		return (NULL);
	str = original;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	return (original);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s);
	dup = ft_calloc(len + 1, sizeof(char));
	if (!dup)
		return (NULL);
	while (len--)
		dup[len] = s[len];
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*s && *s != uc)
		s++;
	if (*s == uc)
		return ((char *)s);
	return (NULL);
}
