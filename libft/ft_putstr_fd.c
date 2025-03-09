/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:38:44 by anamedin          #+#    #+#             */
/*   Updated: 2024/02/16 18:49:08 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s != NULL)
	{
		i = 0;
		while (s[i] != '\0')
		{
			write (fd, &s[i], 1);
			i++;
		}
	}
}

void	ft_init_variables(size_t *i, int *count_w, int *index_substr)
{
	*i = 0;
	*count_w = 0;
	*index_substr = -1;
}

void	ft_init_variables(size_t *i, int *count_w, int *index_substr)
{
	*i = 0;
	*count_w = 0;
	*index_substr = -1;
}
