/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:28:37 by anamedin          #+#    #+#             */
/*   Updated: 2024/04/20 12:24:03 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr_rec(long n)
{
	int	count;
	int	write_return;

	count = 0;
	if (n >= 10)
	{
		write_return = ft_putnbr(n / 10);
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

int	ft_putnbr(long n)
{
	int	count;
	int	write_return;

	count = 0;
	if (n == -2147483648)
		return (ft_print_string("-2147483648"));
	if (n < 0)
	{
		count += ft_putchar('-');
		if (count == -1)
			return (-1);
		n = -n;
	}
	write_return = ft_putnbr_rec(n);
	if (write_return == -1)
		return (-1);
	count += write_return;
	return (count);
}
