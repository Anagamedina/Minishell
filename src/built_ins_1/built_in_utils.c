/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:47:46 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/25 01:37:37 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:54:28 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/21 21:16:01 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*find_env_var(t_list *env_list, char *key)
{
	t_env	*env;

	if (!env_list || !key)
		return (NULL);
	while (env_list != NULL)
	{
		env = (t_env *)env_list->content;
		if (env && env->key && ft_strcmp(env->key, key) == 0)
			return (env);
		env_list = env_list->next;
	}
	return (NULL);
}

void	check_value(char *value, char *line, t_env *env_var)
{
	if (value && ft_strcmp(line, "+="))
		env_var->value = ft_strjoin(env_var->value, value);
	else if (value && ft_strcmp(line, "="))
	{
		free(env_var->value);
		env_var->value = value;
	}
	else if (!value)
		env_var->value = ft_strdup("");
}

t_list	*create_new_env_node(char *key, char *value)
{
	t_env	*new_var;
	t_list	*new_node;

	new_var = init_empty_env_node();
	if (!new_var)
	{
		perror("Error: Failed to create environment variable");
		free(key);
		free(value);
		return (NULL);
	}
	new_var->key = key;
	if (value == NULL)
		new_var->value = ft_strdup("empty");
	else
		new_var->value = value;
	new_var->full_var = ft_strjoin_export(key, value, '=');
	new_node = ft_lstnew(new_var);
	if (!new_node)
	{
		free_env(new_var);
		return (NULL);
	}
	return (new_node);
}

void	print_export(t_list **env_list)
{
	t_list	*tmp;
	t_env	*env_var;

	if (!env_list || !*env_list)
		return;

	tmp = *env_list;
	while (tmp)
	{
		env_var = (t_env *)(tmp->content);
		if (env_var && env_var->key)
		{
			printf("declare -x %s", env_var->key);
			if (env_var->value)
			{
				if (env_var->value[0] != '\0')
					printf("=\"%s\"", env_var->value);
			}
			printf("\n");
		}
		tmp = tmp->next;
	}
}
/*
void	print_export(t_list **env_list)
{
	t_list	*tmp;
	t_env	*env_var;

	if (!env_list || !*env_list)
		return ;
	tmp = *env_list;
	while (tmp != NULL)
	{
		env_var = (t_env *)(tmp->content);
		if (env_var)
		{
			printf("declare -x %s", env_var->key);
			if (env_var->value && ft_strcmp(env_var->value, "empty") == 0)
			{
				continue ;
				// printf(" ");
			}
			else if (env_var->value && ft_strcmp(env_var->value, "") == 0)
				printf("=\"\"");
			else
				printf("=\"%s\"", env_var->value);
			printf("\n");
		}
		tmp = tmp->next;
	}
}
*/

/*
void	update_var(char *line, t_list **env_list)
{
	char	*key;
	char	*value;
	t_env	*env_var;

	key = get_var_name(line);
	value = get_var_value(line);
	env_var = find_env_var(*env_list, key);
	if (env_var == NULL)
	{
		create_new_env_node(key, value);
	}
	else
		check_value(value, line, env_var);
	free(key);
	if (!env_var)
		free(value);
}
*/
