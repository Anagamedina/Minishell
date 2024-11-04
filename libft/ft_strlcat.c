/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:16:21 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/24 10:36:49 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dsize;

	dsize = 0;
	while (dst[dsize] != '\0' && dsize < dstsize)
		dsize++;
	i = dsize;
	while (src[dsize - i] && dsize + 1 < dstsize)
	{
		dst[dsize] = src[dsize - i];
		dsize++;
	}
	if (i < dsize)
		dst[dsize] = '\0';
	return (i + ft_strlen((char *)src));
}

// int main(void)
// {
// 	char des[20] = "hola";
// 	char org[20] = "que tal";
// 	size_t x = 4;
// 	size_t result = ft_strlcat(des, org, x);
// 	printf("%zu", result);
// 	size_t result2 = strlcat(des, org, x);
// 	printf("%zu", result2);
// 	return(0);

// }
