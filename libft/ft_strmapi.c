/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:17:26 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/24 10:36:57 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	char			*s2;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	s2 = (char *) s;
	str = (char *) malloc (sizeof(char) * (ft_strlen(s2)) + 1);
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = f((unsigned int)i, s2[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

// static char transform(unsigned int index, char c) {
//     if (index % 2 == 0)
//         return (c - 32);  // Convierte en mayúscula si es índice par
//     return c;
// }

// int main()
// {
// 	char src[20] = "hola que tal";
// 	char *result = ft_strmapi(src, transform) ;
// 	printf("%s", result);
// 	return(0);
// }
