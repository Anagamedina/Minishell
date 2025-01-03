

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

	if (cmd_path != NULL)
	{
		free(cmd_path);
		return 1;  // Es un comando externo
	}
	return 0;
}


void assign_token_type(t_tokens *token, t_mini *mini)
{
	while (token != NULL)
	{

		if (token->type_token == WORD)
		{
			if (is_builtin_command(token->str))
			{
				token->type_token = BUILTINS;
				printf("Asignado como BUILTINS: %s\n", token->str);
			}
			else if (is_cmd_external(mini, token->str))
			{
				token->type_token = CMD_EXTERNAL;
				printf("Asignado como CMD_EXTERNAL: %s\n", token->str);
			}
			else
			{
				token->type_token = WORD;
				printf("Asignado como WORD: %s\n", token->str);
			}

		}

		token = token->next;
	}

}
