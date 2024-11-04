/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:24:00 by anamedin          #+#    #+#             */
/*   Updated: 2024/02/19 15:20:16 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	c_char;

	c_char = c;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == c_char)
		{
			return ((char *)(&s[len]));
		}
		len--;
	}
	return (NULL);
}
