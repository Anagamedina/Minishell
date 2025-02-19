/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_locals_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:34:14 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/19 23:09:23 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_syntax_name_value(char *new_local_var)
{
	if (!(validate_var_name(new_local_var)))
		return (FALSE);
	if (!(validate_var_value(new_local_var)))
		return (FALSE);
	return (TRUE);
}

t_list	*create_local_vars_list(char *line, t_list *local_vars_list)
{
	t_env	*local_vars;
	t_list	*new_node;

	if (!(validate_syntax_name_value(line)))
	{
		printf("Error: invalid local variable syntax: %s\n", line);
		return (local_vars_list);
	}
	local_vars = init_env_var(line);
	if (!local_vars)
	{
		printf("Error: failed to initialize local variable: %s\n", line);
		return (local_vars_list);
	}
	new_node = ft_lstnew(local_vars);
	if (!new_node)
	{
		free_env(local_vars);
		printf("Error: failed to create list node for: %s\n", line);
		return (local_vars_list);
	}
	ft_lstadd_back(&local_vars_list, new_node);
	return (local_vars_list);
}