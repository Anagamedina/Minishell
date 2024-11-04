/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:39:05 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/24 10:48:33 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
		ptr[i++] = '\0';
}

/*void print_memory(char *str, size_t len)
{
    size_t i = 0;
    while (i < len)
    {
        printf("%d ", (unsigned char)str[i]);
        i++;
    }
    printf("\n");
}

int main()
{
    char buffer[10];
    size_t i = 0;

    while (i < 10)
    {
        buffer[i] = 'A';
        i++;
    }

    print_memory(buffer, 10);
    bzero(buffer, 5);
    printf("Después de bzero:\n");
    print_memory(buffer, 10);

    return 0;
}*/
