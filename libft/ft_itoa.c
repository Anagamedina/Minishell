/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:29:37 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/24 10:37:30 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		sign;

	if (n == 0)
		return (ft_strdup ("0"));
	if (n < 0)
		sign = -1;
	else
		sign = 1;
	len = get_num_len (n);
	str = (char *) malloc ((len +1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (n != 0)
	{
		str [--len] = '0' + (sign * (n % 10));
		n /= 10;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}

// int main(void)
// {
// 	int num = 2;
// 	char *result = ft_itoa(num);
// 	printf("%s", result);
// 	return(0);
// }
