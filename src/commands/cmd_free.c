/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:48:37 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/31 01:04:26 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_command(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->cmd_args)
	{
		while (cmd->cmd_args[i] != NULL)
		{
			free(cmd->cmd_args[i]);
			i ++;
		}
		free(cmd->cmd_args);
	}
	// free(cmd);
}
void free_cmd_list(t_list *cmd_list)
{
	t_list *tmp;
	t_cmd *cmd;
	int i;

	while (cmd_list) {
		tmp = cmd_list->next;
		cmd = (t_cmd *)cmd_list->content;  // Convierte el contenido de la lista a t_cmd
		if (cmd) {
			free(cmd->cmd);  // Libera el comando

			// Libera cmd_args si es un char **
			if (cmd->cmd_args) {
				i = 0;
				while (cmd->cmd_args[i] != NULL) {
					free(cmd->cmd_args[i]);  // Libera cada cadena de argumentos
					i++;
				}
				free(cmd->cmd_args);  // Libera el array de punteros a cadenas
			}

			// Si tienes otras estructuras o listas dentro de cmd, libéralas aquí
			// Por ejemplo, redir_list si existe
			//if (cmd->redir_list) {
				//free(cmd->redir_list);  // Esto dependerá de cómo hayas gestionado la memoria en t_redir
			//}

			free(cmd);  // Libera el comando
		}
		free(cmd_list);  // Libera el nodo de la lista
		cmd_list = tmp;  // Avanza al siguiente nodo
	}
}