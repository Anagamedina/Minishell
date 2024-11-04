/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsignedint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:48:07 by anamedin          #+#    #+#             */
/*   Updated: 2024/04/20 12:23:07 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_unsigned_rec(unsigned int n)
{
	int	count;
	int	write_return;

	count = 0;
	if (n >= 10)
	{
		write_return = ft_unsigned_rec(n / 10);
		if (write_return == -1)
			return (-1);
		count += write_return;
	}
	write_return = ft_putchar(n % 10 + '0');
	if (write_return == -1)
		return (-1);
	count += write_return;
	return (count);
}

unsigned int	ft_unsignedint(unsigned int n)
{
	int	count;
	int	write_return;

	count = 0;
	write_return = ft_unsigned_rec(n);
	if (write_return == -1)
		return (-1);
	count += write_return;
	return (count);
}
