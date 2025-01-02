

#include "../../includes/minishell.h"

int	is_builtin_command(const char *cmd)
{
	return (strcmp(cmd, ECHO) == 0 || strcmp(cmd, EXPORT) == 0 || \
		strcmp(cmd, UNSET) == 0 || strcmp(cmd, ENV) == 0 || \
		strcmp(cmd, CD) == 0 || strcmp(cmd, PWD) == 0 || \
		strcmp(cmd, EXIT) == 0);
}

int is_cmd_external(t_mini *mini,  char *cmd)
{
	if (!mini->exec || !mini->exec->paths)
		return 0;

	char *cmd_path = get_cmd_path(cmd, mini->exec->paths);
	printf("--------cmd_path: [%s]\n", ft_strdup(cmd_path));

	// Si cmd_path no es NULL, significa que se encontro un comando externo
	if (cmd_path != NULL)
	{
		free(cmd_path);
		return 1;  // Es un comando externo
	}
	return 0;
}


/*void assign_token_type(t_tokens *token, t_exec *exec_info)
{
	// Verifica si es un comando interno (builtin)
	if (is_builtin_command(token->str))
	{
		token->type_token = BUILTINS;
	}
		// Si no es un comando interno, verifica si es un comando externo
	else if (is_cmd_external(exec_info, token->str))  // Verifica si es un comando externo
	{
		token->type_token = CMD_EXTERNAL;
	}
	else
	{
		token->type_token = WORD;
	}

}*/