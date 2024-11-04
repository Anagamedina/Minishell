/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:12:00 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/21 20:36:09 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size_s1;
	size_t	i;
	char	*duplicate;

	size_s1 = ft_strlen(s1);
	if (!s1)
		return (NULL);
	duplicate = malloc(sizeof(char) * (size_s1 + 1));
	if (!duplicate)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		duplicate[i] = s1[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

/*int main(void)
{
	char s1[] = "hola ana";
	char *result = ft_strdup(s1);
	printf("%s", result);
	return(0);


}*/
