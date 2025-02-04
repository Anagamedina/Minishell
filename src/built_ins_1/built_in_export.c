/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/04 18:55:23 by dasalaza         ###   ########.fr       */
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
void	init_process_export(t_cmd *curr_command, t_list *env_list)
{
	char	*name_and_value;
	char	*var_name;
	char	*var_value;

	name_and_value = curr_command->cmd_args[1];

	// printf("curr_command->cmd_args[1]: [%s]\n", name_and_value);
	var_name = get_var_name(name_and_value);
	var_value = get_var_value(name_and_value);

	printf("var_name: [%s]\n", var_name);
	printf("var_value: [%s]\n", var_value);
	int		condition1 = validate_var_name(name_and_value);
	int		condition2 = validate_var_value(name_and_value);

	// if (validate_var_name(var_name) == 1 && validate_var_value(var_value) == 1)
	if (condition1 == TRUE && condition2 == TRUE)
	{
		create_new_key(name_and_value, var_name, var_value, &env_list);
		// update_var(var_name, &env_list);
	}
	else
	{
		printf("Error: formato no válido para 'export'.\n");
	}
}

/*
 * Maneja el caso donde el primer token es una asignación local
 * o un comando desconocido.
 * key=value
 * key=
 */
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

/*
 * Gestiona el comando ingresado por el usuario.
 * Verifica si el primer token es "export" o "key=value" y delega a las funciones correspondientes.
 */

// **************** MAIN FUNCTION ******************

/*
void	builtin_export(t_mini *mini)
{
	t_cmd		*cmd_01;
	t_tokens 	*first_token;

	first_token = mini->tokens->content;
	cmd_01 = mini->exec->first_cmd->content;
	if ((ft_strcmp(cmd_01->cmd, "export") == 0))
	{
		only_export(mini->env);
	}
}
*/

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	first_arg;

	i = 1;
	first_arg = 1; // Usamos esta variable para evitar agregar un espacio antes del primer argumento

	//printf("[");
	while (cmd->cmd_args[i])
	{
		if (cmd->cmd_args[i][0] != first_arg)
		{
			printf("%s", cmd->cmd_args[i]);
			if (cmd->cmd_args[i][0] != '\0' && cmd->cmd_args[i + 1]) // Verifica si hay un siguiente argumento()
				printf(" ");
		//	first_arg = 0; // Después del primer argumento, se agregan espacios

		}

		i++;
	}
	printf("\n");
}
