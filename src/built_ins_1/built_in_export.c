/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/29 12:36:05 by catalinab        ###   ########.fr       */
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
void	init_process_export(t_list *tokens, t_list *env_list)
{
	t_tokens	*next_token;
	// t_tokens	*token_first;

	next_token = tokens->next->content;
	// token_first = tokens->content;
	// printf("----------%s\n", token_first->str);
	//		caso 02: line = export
	// if (token_first)
	// {
	// 	printf("entra en only export\n");
	// 	only_export(env_list);
	// 	return;
	// }
	if (validate_var_name(next_token->str) && validate_var_value(next_token->str))
	{
		update_var(next_token->str, &env_list);
		return;
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

void	builtin_export(t_mini *mini)
{
	t_cmd	*cmd_01;
	t_tokens 	*first_token;

	first_token = mini->tokens->content;
	cmd_01 = mini->exec->first_cmd->content;
	if ((ft_strcmp((char *)cmd_01->cmd, "export") == 0))
	{
		if (first_token->next == NULL)
		{
			printf("entro en export sin variable\n");
			only_export(mini->env);
		}
		else
		{
			printf("entro en export con variable\n");
			init_process_export(mini->tokens, mini->env);
		}
		
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
