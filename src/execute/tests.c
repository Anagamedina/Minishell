

#include "../../includes/minishell.h"

/*void print_paths(char **paths)
{
	int i = 0;
	if(paths == NULL)
	{
		printf("NO paths found. \n");
		return;
	}
	while(paths[i])
	{
		printf("path[%d]: %s\n", i, paths[i]);
		i++;
	}
}
*/


void	print_list_token(t_list *tokens_list)
{
	t_list		*current;
	t_tokens	*token;
	int			i;

	current = tokens_list;
	i = 1;
	while (current != NULL)
	{
		token = (t_tokens *)current->content;
		printf("TOKEN [%i] :\n", i);
		printf("str: [%s]\n", token->str);
		printf("type: [%i]\n", token->type_token);
		printf("len: [%zu]\n", token->length);
		i ++;
		current = current->next;
		printf("-------------------\n");
	}
}


void	print_list_token_str(t_list *tokens_list)
{
	t_list *current;
	t_tokens *token;
	int i;

	current = tokens_list;
	i = 1;
	while (current != NULL)
	{
		token = (t_tokens *)current->content;
		printf("TOKEN [%i] :\n", i);
		printf("str: [%s]\n", token->str);

		// Imprime el tipo del token
		printf("type: [%i] ", token->type_token);
		if (token->type_token == BUILTINS)
			printf("(BUILTIN)");
		else if (token->type_token == CMD_EXTERNAL)
			printf("(EXTERNAL COMMAND)");
		else if (token->type_token == WORD)
			printf("(WORD)");
		else if (token->type_token == PIPE)
			printf("(PIPE)");
		else if (token->type_token == REDIR_IN)
			printf("(REDIR_IN)");
		else if (token->type_token == REDIR_OUT)
			printf("(REDIR_OUT)");
		// Agrega más tipos según lo que hayas definido en tu enum.

		printf("\n");
		printf("len: [%zu]\n", token->length);
		i++;
		current = current->next;
		printf("-------------------\n");
	}
}

/*void	print_list_token_str(t_list *tokens_list)
{
	t_list		*current;
	t_tokens	*token;

	current = tokens_list;
	printf("[");
	while (current != NULL)
	{
		token = (t_tokens *)current->content;
		if (!is_builtin_command(token->str))
		{
			printf("%s", token->str);
			if (current->next != NULL)
				printf(" ");
		}
		current = current->next;
	}
	printf("]");
	printf("\n");
}*/

/*
int	check_lowercase_tokens(t_list *tokens_list)
{
	t_list		*current;
	t_tokens	*token;
	int 		i;

	current = tokens_list;
	while (current->next != NULL)
	{
		token = (t_tokens *)current->content;
		if (token->type_token == WORD)
		{
			i = 0;
			while (token->str[i])
			{
				if (token->str[i] < 'a' || token->str[i] > 'z')
					return (FALSE);
				i++;
			}
		}
		current = current->next;
	}
	return (TRUE);
}
*/
/*void print_paths(char **paths)
{
	if (!paths)
	{
		printf("No hay rutas definidas.\n");
		return;
	}

	printf("Rutas disponibles:\n");
	int i = 0;
	while (paths[i])
	{
		printf("[%s]\n", paths[i]);
		i++;
	}
}*/


// Esta función divide el comando en flags y los guarda en cmd_flags
/*void process_flags(t_cmd *cmd, char *cmd_str)
{
	char **cmd_split;

	// Dividir el comando en tokens separados por espacios
	cmd_slit = ft_split(cmd_str, ' ');
	if (!cmd_split)
	{
		perror("Error: ft_split cmd failed");
		return;
	}

	//cmd->cmd_flags = ft_calloc(1, sizeof(char *));
	//if (!cmd->cmd_flags)
	//{
		//perror("Error al asignar memoria para cmd_flags");
		//free(cmd_split);
		//return;
	//}
	cmd->cmd_split = cmd_split;
}*/