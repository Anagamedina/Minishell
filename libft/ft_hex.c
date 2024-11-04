/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 02:46:20 by anamedin          #+#    #+#             */
/*   Updated: 2024/04/19 02:16:06 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hex(unsigned long nbr, const char str)
{
	int		count;
	char	*base;

	count = 0;
	if (str == 'x' || str == 'p')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nbr >= 16)
	{
		count += ft_hex(nbr / 16, str);
		if (count == -1)
			return (-1);
	}
	if ((ft_putchar(base[nbr % 16]) == -1))
		return (-1);
	count++;
	return (count);
}
