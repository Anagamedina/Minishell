/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:35:48 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/16 12:08:10 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	size_s1;
	size_t	size_s2;
	size_t	i;

	size_s1 = 0;
	size_s2 = 0;
	if (s1)
		size_s1 = ft_strlen(s1);
	if (s2)
		size_s2 = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (size_s1 + size_s2 + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < (size_s1 + size_s2))
	{
		if (i < size_s1)
			ptr[i] = s1[i];
		else
			ptr[i] = s2[i - size_s1];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}


/*
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	size_s1;
	size_t	size_s2;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	ptr = malloc(sizeof(char ) * (size_s1 + size_s2 + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < (size_s1 + size_s2))
	{
		if (i < size_s1)
			ptr[i] = s1[i];
		else
			ptr[i] = s2[i - size_s1];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
*/
/*
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	size_s1;
	size_t	size_s2;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	ptr = malloc(sizeof(char ) * (size_s1 + size_s2 + 2));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < (size_s1 + size_s2) + 1)
	{
		if (i < size_s1)
			ptr[i] = s1[i];
		else if (i != 0 && i == size_s1)
			ptr[i] = ' ';
		else if (i >= size_s1 + 1)
			ptr[i] = s2[i - size_s1 - 1];
		i ++;
	}
	ptr[i] = '\0';
	return (ptr);
}
*/
