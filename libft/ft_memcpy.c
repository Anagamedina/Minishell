/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:54:54 by anamedin          #+#    #+#             */
/*   Updated: 2024/02/19 15:00:37 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dstr;
	const unsigned char	*sstr;

	dstr = dst;
	sstr = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n--)
		*dstr++ = *sstr++;
	return (dst);
}
