/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:32:02 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/27 12:29:16 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:32:02 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/27 00:20:11 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_var_name(const char *line)
{
	int	i;

	if (line[0] == '+' || line[0] == '=')
		return (FALSE);
	if (!(ft_isalpha(line[0]) || line[0] == '_'))
		return (FALSE);
	i = 1;
	while (line[i] != '\0' && line[i] != '=' && !(line[i] == '+' && \
		line[i + 1] == '='))
	{
		if (!(ft_isalnum(line[i]) || line[i] == '_'))
			return (FALSE);
		i ++;
	}
	if (line[i] == '+' && line[i + 1] == '=')
	{
		if (line[i + 2] == '\0')
			return (FALSE);
	}
	return (TRUE);
}

int	validate_var_value(const char *line)
{
	int	i;

	if (!line)
		return (FALSE);
	i = 0;
	while (line[i] != '=' && line[i] != '+' && line[i] != '\0')
		i ++;
	if (line[i] == '+' && line[i + 1] == '=')
		i ++;
	if (line[i] == '\0')
		return (TRUE);
	i ++;
	while (line[i] != '\0')
	{
		if (!(ft_isascii(line[i])))
			return (FALSE);
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
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '=')
		i ++;
	len = i;
	if (len == 0)
		return (NULL);
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (NULL);
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
	int		len;
	char	*var_value;
	int		positon_of_equal;

	if (!line)
		return (NULL);
	len = 0;
	while (line[len] != '\0')
		len ++;
	positon_of_equal = ft_strchr_c(line, '=');
	if (positon_of_equal == -1)
		return (NULL);
	if (positon_of_equal == len - 1)
		return (ft_strdup(""));
	var_value = malloc(sizeof(char) * (len - positon_of_equal));
	if (!var_value)
		return (NULL);
	ft_strcpy(var_value, &line[positon_of_equal + 1]);
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
		if (curr_env && curr_env->key \
		&& ft_strcmp(key_to_find, curr_env->key) == 0)
			return (curr_env->value);
		curr_node = curr_node->next;
	}
	return (NULL);
}
