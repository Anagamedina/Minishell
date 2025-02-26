/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_part_one_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:45:31 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/26 20:45:58 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * ft_strjoin_export - concat two strings with a character separator.
 *
 * - `c`: character separator (default: `=`).
 * A string in the format `s1=c+s2`.
 */

char	*ft_strjoin_export(const char *s1, const char *s2, char c)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!result)
		return (NULL);
	if (s1)
		ft_memcpy(result, s1, len1);
	result[len1] = c;
	if (s2)
		ft_memcpy(result, s2, len2);
	result[len1 + len2 + 1] = '\0';
	return (result);
}
