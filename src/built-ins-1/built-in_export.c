/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:53:35 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/26 13:08:18 by anamedin         ###   ########.fr       */
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
void	init_process_export(t_list *tokens, t_list *env_list)
{
	t_tokens	*next_token;

	// Si hay un siguiente token, verificar si tiene formato "key=value"
	next_token = tokens->next->content;
//	TODO: ana :)
//	hay un error: al momento de agregar una variable nueva
//	y lo imprimimos, sale correcto pero si volvemos a crear una variable nueva
//	y la imprimimos, sale error de perdida de variable
	if (validate_var_name(next_token->str) && validate_var_value(next_token->str))
	{
		export_var(next_token->str, &env_list);
		return;
	}
////		caso 02: line = export
/*
	else if ()
	{

	}
*/
	else	// Si no es válido, mostrar un error
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

void	builtin_export(t_mini *mini)
{
	t_cmd	*cmd_01;

	cmd_01 = mini->cmds->content;
	if ((ft_strcmp((char *)cmd_01->cmd, "export") == 0))
	{
		init_process_export(mini->token, mini->env);
	}
	/*else if ((ft_strcmp((char *)cmd_01->cmd, "unset") == 0))
	{

	}
	else if ((ft_strcmp((char *)cmd_01->cmd, "env") == 0))
	{
		print_env_list(mini->env);
	}*/
	else
		return;
}
