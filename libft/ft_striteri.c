/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:57:11 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/24 10:36:41 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f((unsigned int)i, &s[i]);
		i++;
	}
}

// void transform(unsigned int index, char *c) {
//     if (index % 2 == 0 && *c >= 'a' && *c <= 'z') 
// 	{
//         *c = *c - 32;
//     }
// }int main()
// {
// 	char src[20] = "hola que tal";
// 	ft_striteri(src, transform) ;
// 	printf("%s", src);
// 	return(0);
// }
