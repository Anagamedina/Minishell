/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:53:35 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/21 16:53:41 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "../../includes/minishell.h"

/*
 * Maneja el caso donde el primer token es "export".
 * Puede listar variables de entorno o agregar/modificar una.
 */
void	handle_export(t_list **tokens, t_list **env_list)
{
	t_tokens	*next_token;

	// Si solo es "export", listar las variables de entorno
	if (!(*tokens)->next)
	{
		only_export(*env_list);
		return;
	}

	// Si hay un siguiente token, verificar si tiene formato "key=value"
	next_token = (t_tokens *)(*tokens)->next->content;
	if (ft_strrchr_c(next_token->str, '='))
	{
		export_var(next_token->str, env_list);
		return;
	}

	// Si no es válido, mostrar un error
	printf("Error: formato no válido para 'export'.\n");
}

/*
 * Maneja el caso donde el primer token es una asignación local
 * o un comando desconocido.
 */
void	handle_local_or_unknown(t_tokens *first_token, t_list **local_vars)
{
	char	*line = first_token->str;

	// Si contiene un '=', es una variable local
	if (ft_strrchr_c(line, '='))
	{
		create_local_var(line, local_vars);
		return;
	}

	// Caso de comando no reconocido
	printf("Error: comando no reconocido.\n");
}

/*
 * Gestiona el comando ingresado por el usuario.
 * Verifica si el primer token es "export" o "key=value" y delega a las funciones correspondientes.
 */
void	handle_input(t_list **tokens, t_list **env_list, t_list **local_vars)
{
	t_tokens	*first_token;
	char	*line;

	if (!tokens || !*tokens)
		return;
	first_token = (t_tokens *)(*tokens)->content;
	line = first_token->str;

	// Delegar según el contenido del primer token
	if (ft_strcmp(line, "export") == 0)
		handle_export(tokens, env_list);
	else
		handle_local_or_unknown(first_token, local_vars);
}


