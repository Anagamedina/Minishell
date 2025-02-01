/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:56:30 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/01 13:02:16 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"




int parse_redir(t_mini *mini)
{
	t_list *token_list = mini->token;
	t_tokens *curr_token;
	t_cmd *last_cmd = NULL;  // Para asociar redirecciones al último comando encontrado

	while (token_list)
	{
		curr_token = (t_tokens *)token_list->content;

		// Si encontramos un comando, actualizamos last_cmd
		if (curr_token->type_token == CMD_EXTERNAL || curr_token->type_token == BUILTINS)
			last_cmd = (t_cmd *)token_list->content;

		// Si encontramos una redirección, la asociamos al último comando
		if (curr_token->type_token == REDIR_IN || curr_token->type_token == REDIR_OUT || curr_token->type_token == REDIR_APPEND)
		{
			if (!token_list->next)
			{
				printf("Error: Redirección '%s' sin archivo.\n", curr_token->str);
				return (FALSE);
			}
			t_tokens *next_token = (t_tokens *)token_list->next->content;

			if (next_token->type_token != FILENAME)
			{
				printf("Error: Redirección '%s' debe ir seguida de un archivo.\n", curr_token->str);
				return (FALSE);
			}

			if (!last_cmd)
			{
				printf("Error: Redirección '%s' sin comando asociado.\n", curr_token->str);
				return (FALSE);
			}

			// Agregar redirección al comando correspondiente
			// add_redirection_to_cmd(last_cmd, next_token);
		}

		token_list = token_list->next;
	}
	return (TRUE);
}






/*int parse_redir(t_mini *mini)
{
	t_list		*token_list;
	t_tokens	*curr_token;
	t_cmd		*last_cmd = NULL;


	token_list = mini->token;
	while (token_list != NULL)
	{
		curr_token = (t_tokens *)token_list->content;
		if (token_list->next != NULL)
		{
			t_tokens *next_token = (t_tokens *)token_list->next->content;
			if (curr_token->type_token == REDIR_IN || curr_token->type_token == REDIR_OUT || curr_token->type_token == REDIR_APPEND)
			{
				if (next_token->type_token != FILENAME)
				{
					printf("Error: Redirección '%s' debe ir seguida de un archivo.\n", curr_token->str);
					return (FALSE);
				}
			}
		}
		else if (check_repeat_redir(mini->token) == FALSE)
		{
			printf("Error: Redirecciones consecutivas o mal colocadas.\n");
			return (FALSE);
		}

		else if (curr_token->type_token == REDIR_IN || curr_token->type_token == REDIR_OUT || curr_token->type_token == REDIR_APPEND)
		{
			printf("Error: Redirección '%s' sin archivo ultimo token.\n", curr_token->str);
			return (FALSE);
		}
		token_list = token_list->next;
	}
	return (TRUE);
}
*/



/*int  	check_file(t_mini *mini, t_tokens *token)
{
	t_list *current = mini->token;

	if (!current || !current->next)
	{
		printf("Error: Redirección de salida sin archivo.\n");
		return (FALSE);
	}
	t_tokens *next_token = (t_tokens *)current->next->content;
	if (next_token->type_token != WORD)
	{
		printf("Error: Redirección debe ir seguida de un archivo.\n");
		return (FALSE);	
	}

	return (TRUE);

}*/