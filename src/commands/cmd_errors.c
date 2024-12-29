#include "../../includes/minishell.h"

// Verifica si el token es nulo. Si lo es, muestra un mensaje de error, libera la lista de comandos y devuelve FALSE.
int error_empty_token(t_tokens *token, t_list *cmd_list)
{
	if (!token)
	{
		printf("Error: empty token\n");
		free_command_list((t_cmd *) cmd_list);
		return (FALSE);
	}
	return (TRUE);
}

// Verifica si la creación de un comando falló. Si es así, muestra un mensaje de error, libera la lista de comandos y devuelve FALSE.
int error_cmd_creation(t_cmd *cmd, t_list *cmd_list)
{
	if (!cmd)
	{
		printf("Error: can't create command.\n");
		free_command_list((t_cmd *) cmd_list);
		return (FALSE);
	}
	return (TRUE);
}

// Verifica si la creación de un nodo falló. Si es así, muestra un mensaje de error, libera el comando y la lista de comandos, y devuelve FALSE.
int error_node_creation(t_list *node, t_cmd *cmd, t_list *cmd_list)
{
	if (!node)
	{
		printf("Error: can't create command.\n");
		free_command(cmd);
		free_command_list((t_cmd *) cmd_list);
		return (FALSE);
	}
	return (TRUE);
}

// Maneja errores al crear un nuevo comando o nodo. Libera memoria de comandos y nodos creados previamente, limpia la lista y devuelve NULL.
t_list *handle_error(t_list *cmds_list, t_list *new_cmd, t_list *new_node)
{
	if (new_cmd)
		free_command((t_cmd *)new_cmd);
	if (new_node)
		free(new_node);
	ft_lstclear(&cmds_list, (void (*)(void *)) free_command);
	return (NULL);
}