/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhernan <orhernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:05:07 by orhernan          #+#    #+#             */
/*   Updated: 2025/10/30 14:53:23 by orhernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned char	*p;
	int				total;

	if (size == 0 || count == 0)
		return (malloc(0));
	if (count > 0 && size > SIZE_MAX / count)
		return (NULL);
	total = count * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	p = (unsigned char *)ptr;
	while (total > 0)
	{
		*p++ = '\0';
		total--;
	}
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
	char	*original;
	char	*str;
	size_t	str_len;
	int		i;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	str_len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc(str_len + 1, sizeof(char));
	original = str;
	i = 0;
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++i])
		str[i] = s2[i];
	return (original);
}

char	*ft_strdup(const char *s)
{
	char	*tmp;
	char	*tmp_aux;
	int		count;

	count = ft_strlen(s);
	tmp = (char *)ft_calloc(count + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	tmp_aux = tmp;
	while (*s)
	{
		*tmp = *s;
		s++;
		tmp++;
	}
	return (tmp_aux);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char		*substring;
	size_t		str_len;
	size_t		i;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if (str_len - start < len)
		len = str_len - start;
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
