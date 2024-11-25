/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:53:35 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/25 16:11:41 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Maneja el caso donde el primer token es "export".
 * Puede listar variables de entorno o agregar/modificar una.
 * caso 01:
 * line = export
 * caso 02:
 * line = export key=value
 * case 03:
 * error
 */
void	init_process_export(t_list *tokens, t_list *env_list)
{
	t_tokens	*next_token;

	// Si hay un siguiente token, verificar si tiene formato "key=value"
	next_token = tokens->next->content;
	if (validate_var_name(next_token->str) && validate_var_value(next_token->str))
	{
		export_var(next_token->str, env_list->content);
		return;
	}
	else	// Si no es válido, mostrar un error
		printf("Error: formato no válido para 'export'.\n");
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
/*
void	builtin_export(t_list **tokens, t_list **env_list, t_list **local_vars)
{
	t_tokens	*first_token;
	char		*line;

	if (!tokens || !*tokens)
		return;
	first_token = (t_tokens *)(*tokens)->content;
	line = first_token->str;
	// Delegar según el contenido del primer token
	if (ft_strcmp(line, "export") == 0)
		init_process_export(*tokens, *env_list);
	else
		handle_local_or_unknown(first_token, local_vars);
}
*/