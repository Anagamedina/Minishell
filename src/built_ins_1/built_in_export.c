/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/10 23:13:34 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:53:35 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/29 12:08:36by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Maneja el caso donde el primer token es "export".
 * Puede listar variables de entorno o agregar/modificar una.
 * caso 01:
 * line = export key=value
 * caso 02:
 * line = export
 * case 03:
 * error
 */

static int update_var_exist(char *var_name, char *new_value, t_list **env_list)
{
	t_list	*current_node;
	t_env	*current_var;

	current_node = *env_list;
	while (current_node)
	{
		current_var = (t_env *)current_node->content;
		if (ft_strcmp(current_var->key, var_name) == 0)
		{
			free(current_var->value);
			if (new_value != NULL)
				current_var->value = ft_strdup(new_value);
			else
				current_var->value = ft_strdup("");
			return (TRUE);
		}
		current_node = current_node->next;
	}
	return (0);
}

void	export_variable(t_cmd *curr_command, t_list** env_list)
{
	char	*key_value;
	char	*var_name;
	char	*var_value;
	t_list	*new_var_env;

	if (!curr_command->cmd_args[1] || !curr_command->cmd_args[1] || !env_list)
		return ;
	key_value = curr_command->cmd_args[1];
	new_var_env = NULL;
	var_name = get_var_name(key_value);
	var_value = get_var_value(key_value);
	if (validate_var_name(var_name) == 1 && validate_var_value(var_value) == 1)
	{
		if (!update_var_exist(var_name, var_value, env_list))
		{
			new_var_env = create_new_key(key_value, var_name, var_value);
			if (new_var_env)
			{
				if (*env_list == NULL)
					*env_list = new_var_env;
				else
					ft_lstadd_back(env_list, new_var_env);
			}
		}
	}
	else
		printf("Error: formato no válido para 'export'.\n");
}

/*
 * Maneja el caso donde el primer token es una asignación local
 * o un comando desconocido.
 * key=value
 * key=
 */
/*
void	handle_local_or_unknown(t_tokens *first_token, t_list **local_vars_list)
{
	char	*line;

	line = first_token->str;
	if (validate_var_name(line) == TRUE && validate_var_value(line) == TRUE)
	{
		create_local_vars_list(line, *local_vars_list);
		return;
	}
	else
		printf("Error: comando no reconocido.\n");
}
*/
