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

	if (!mini->exec || !mini->exec->paths)
		return FALSE;

	cmd_path = get_cmd_path(token, mini->exec->paths);
	if (cmd_path != NULL)
	{
		printf("--------cmd_path: [%s]\n", cmd_path);
		free(cmd_path);
		return (TRUE);
	}
	else
	{
		printf("--------cmd_path: [NULL]\n");
		return (FALSE);
	}
}

