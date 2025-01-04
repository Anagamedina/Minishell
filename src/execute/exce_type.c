#include "../../includes/minishell.h"

int	is_builtin_command(const char *cmd)
{
	return (strcmp(cmd, ECHO) == 0 || strcmp(cmd, EXPORT) == 0 || \
		strcmp(cmd, UNSET) == 0 || strcmp(cmd, ENV) == 0 || \
		strcmp(cmd, CD) == 0 || strcmp(cmd, PWD) == 0 || \
		strcmp(cmd, EXIT) == 0);
}

int is_cmd_external(t_mini *mini, t_tokens *token)
{
	char		*cmd_path;

	if (!mini || !mini->token)
		return FALSE;

	// Verificar que las rutas estén disponibles
	if (!mini->exec || !mini->exec->paths)
		return FALSE;

	// Buscar el path del comando
	cmd_path = get_cmd_path(token, mini->exec->paths);

	if (cmd_path != NULL)
	{
		printf("--------cmd_path: [%s]\n", cmd_path);  // Imprimir el comando encontrado
		free(cmd_path);  // Liberar memoria asignada por get_cmd_path
		return (TRUE);  // Es un comando externo
	}
	else
	{
		printf("--------cmd_path: [NULL]\n");
		return (FALSE);
	}
}

