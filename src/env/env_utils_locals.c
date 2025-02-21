/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_locals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:04:39 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/21 14:43:54 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_var_name(const char *line)
{
	int	i;

	if (!(ft_isalpha(line[0]) || line[0] == '_'))
	{
		// write(2, "bash: export: invalid variable name\n", 36);
		return (FALSE);
	}
	i = 1;
	while (line[i] != '\0' && line[i] != '=')
	{
		if (!(ft_isalnum(line[i]) || line[i] == '_'))
		{
			// write(2, "bash: export: invalid variable name\n", 36);
			return (FALSE);
		}
		i ++;
	}
	return (TRUE);
}

int	validate_var_value(const char *line)
{
	int	i;

	if (!line)
	{
		perror("bash: export: NULL value");
		return (FALSE);
	}
	i = 0;
	while (line[i] != '=' && line[i] != '\0')
		i ++;
	if (line[i] == '\0')
		return (TRUE);
	i ++;
	while (line[i] != '\0')
	{
		if (!(ft_isascii(line[i])))
		{
			write(2, "bash: export: invalid character in value\n", 42);
			return (FALSE);
		}
		i ++;
	}
	return (TRUE);
}

char	*get_var_name(const char *line)
{
	int		i;
	int		len;
	char	*var_name;

	if (!line || line[0] == '=' || line[0] == '\0')
	{
		// perror("bash: export");
		return (NULL);
	}
	i = 0;
	while (line[i] != '\0' && line[i] != '=')
		i ++;
	len = i;
	if (len == 0)
	{
		// perror("bash: export");
		return (NULL);
	}
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
	{
		// perror("bash: export");
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		var_name[i] = line[i];
		i ++;
	}
	var_name[i] = '\0';
	return (var_name);
}

char	*get_var_value(char *line)
{
	int		i;
	int		len;
	char	*var_value;
	int		positon_of_equal;

	if (!line)
		return (NULL);
	len = (int) ft_strlen(line);
	positon_of_equal = ft_strchr_c(line, '=');
	if (positon_of_equal == -1)
		return (NULL);
	if (positon_of_equal == len - 1)
		return (ft_strdup(""));
	var_value = malloc(sizeof(char) * (len - positon_of_equal));
	if (!var_value)
		return (NULL);
	i = 0;
	positon_of_equal ++;
	while (line[positon_of_equal] != '\0')
		var_value[i++] = line[positon_of_equal++];
	var_value[i] = '\0';
	return (var_value);
}

char	*get_variable_in_env_list(t_list *env_list, char *key_to_find)
{
	t_list	*curr_node;
	t_env	*curr_env;

	if (!key_to_find || !env_list)
		return (NULL);
	curr_node = env_list;
	while (curr_node)
	{
		curr_env = (t_env *) curr_node->content;
		if (ft_strcmp(key_to_find, curr_env->key) == 0)
			return (curr_env->value);
		curr_node = curr_node->next;
	}
	return (NULL);
}
