/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:41:08 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/21 15:32:46 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *) malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero (ptr, (count * size));
	return (ptr);
}

/*void	print_memory(char *str , size_t len )
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		printf("%d", (unsigned char)str[i]);
		i++;
	}
	printf("\n");
}

int	main(void)
{
	char	*str;

	str = (char *)ft_calloc(10 , sizeof(char));
	if (!str)
		return (1);
	print_memory(str, 10);
	free(str);
}*/
