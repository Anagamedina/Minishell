/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:41:55 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/16 20:15:46 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haysta, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*needle)
		return ((char *) haysta);
	while ((haysta[i] != '\0') && (i < len))
	{
		if (haysta[i] == needle[0])
		{
			while ((needle[j] != '\0')
				&& (haysta[i + j] == needle[j])
				&& ((i + j) < len))
			{
				if (needle[j + 1] == '\0')
					return ((char *) &haysta[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
