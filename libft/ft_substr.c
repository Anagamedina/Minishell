/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:25:58 by anamedin          #+#    #+#             */
/*   Updated: 2024/02/20 12:20:36 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_check_size(size_t size_s, size_t len, int start)
{
	size_t	len_new_ptr;

	if (len + start <= size_s)
		len_new_ptr = len;
	else
	{
		if ((size_t)start >= size_s)
			len_new_ptr = 0;
		else
			len_new_ptr = size_s - start;
	}
	return (len_new_ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	len_substr;
	size_t	size_s;
	size_t	i;

	size_s = ft_strlen(s);
	len_substr = ft_check_size(size_s, len, start);
	substr = (char *) malloc(len_substr + 1);
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len_substr && s[start + i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
