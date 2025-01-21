/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:06:30 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/17 17:12:03 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



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
