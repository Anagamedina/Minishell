/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:53:13 by anamedin          #+#    #+#             */
/*   Updated: 2024/07/25 11:53:36 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

int	ft_strchr_c(char *s, char c)
{
	int	index;

	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

char	*str_join(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	size_s1;
	size_t	size_s2;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	ptr = (char *) malloc(sizeof(char) * (size_s1 + size_s2 + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		ptr[size_s1 + i] = s2[i];
		i++;
	}
	ptr[size_s1 + i] = '\0';
	return (ptr);
}

char	*sub_str(const char *s, size_t start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	size;

	size = ft_strlen(s);
	if (start + len < size)
		size = len;
	else
	{
		if (start > size)
			size = 0;
		else
			size = size - start;
	}
	ptr = (char *)malloc(size + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
