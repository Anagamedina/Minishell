/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_part_one_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:24:37 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/07 18:28:51 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_name_append(char *arg)
{
	int		i;
	char	*var_name;

	i = 0;
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
		i++;
	var_name = ft_substr(arg, 0, i);
	return (var_name);
}

char	*get_var_value_append(char *arg)
{
	char	*value_start;
	char	*var_value;

	var_value = NULL;
	value_start = ft_strchr(arg, '=');
	if (!value_start)
		return (NULL);
	var_value = ft_strdup(value_start + 1);
	return (var_value);
}

char	*ft_strjoin_export(const char *s1, char c, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	result = NULL;
	len1 = 0;
	len2 = 0;
	if (!s1 || !s2)
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
