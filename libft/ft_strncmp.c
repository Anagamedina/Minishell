/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:57:58 by anamedin          #+#    #+#             */
/*   Updated: 2024/02/18 21:03:30 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;
	int				diff;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (i < n && us1[i] != '\0' && us2[i] != '\0')
	{
		diff = us1[i] - us2[i];
		if (diff != 0)
			return (diff);
		i++;
	}
	if (i != n)
		return (us1[i] - us2[i]);
	return (0);
}
