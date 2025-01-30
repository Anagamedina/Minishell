

#include "../../includes/minishell.h"

int  	check_file(t_mini *mini, t_tokens *token)
{
	t_list *current = mini->token;

	// Buscar el token en la lista
	while (current && current->content != token)
		current = current->next;

	if (!current || !current->next)
	{
		printf("Error: Redirección de salida sin archivo.\n");
		return (FALSE);
	}

	// Obtener el siguiente token
	t_tokens *next_token = (t_tokens *)current->next->content;
	printf("El siguiente token es: %s\n", next_token->str);

	// Verificar que el siguiente token es un archivo valido
	if (next_token->type_token != WORD)
	{
		printf("Error: Redirección debe ir seguida de un archivo.\n");
		return (FALSE);	
	}

}


int  	parse_redir(t_mini *mini)
{
	t_list *token_list;
	t_tokens *curr_token;

	token_list = mini->token;
	while (token_list != NULL)
	{
		curr_token = (t_tokens *)token_list->content;
		if (curr_token->type_token == REDIR_IN || curr_token->type_token == REDIR_OUT || curr_token->type_token == REDIR_APPEND)
		{
			if (check_file(mini, curr_token) == FALSE)
				return (FALSE);	
		}
		else 
			break;

		token_list = token_list->next;
	}
}
