#include "../../includes/minishell.h"

// Verifica si el token es nulo. Si lo es, muestra un mensaje de error, libera la lista de comandos y devuelve FALSE.
int error_empty_token(t_tokens *token, t_list *cmd_list)
{
	if (!token)
	{
		printf("Error: empty token\n");
		free_cmd_list(cmd_list);
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
		free_cmd_list(cmd_list);
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
		free_cmd_list(cmd_list);
		return (FALSE);
	}
	return (TRUE);
}
