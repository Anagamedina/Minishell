/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:30:20 by anamedin          #+#    #+#             */
/*   Updated: 2024/12/03 14:09:56 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	i = 0;
//	while(s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' )
	while(s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char )s2[i]);
}

//	(*tokens)->str
int	set_token_type(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (REDIR_INPUT);
	else if (ft_strcmp(str, ">") == 0)
		return (REDIR_OUTPUT);
	else if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, ">>") == 0)
		return (CONCAT_OUTPUT);
	else if (ft_strcmp(str, ";") == 0)
		return (DELIMITER);
	else if (str && ft_strlen(str) > 0)
		return (WORD);
	else
		return (NULL_TYPE);	//error en seleccionar!!!
}

// Función que verifica si el token es un built-in
static int	is_builtin(char *str)
{
	char *built_ins[] = BUILTINS_LIST;
	int i = 0;

	while (built_ins[i])
	{
		if (ft_strcmp(str, built_ins[i]) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

// Función que actualiza los tokens a built-ins si corresponde
void	update_words_to_builtin(t_list *tokens_list)
{
	t_list *current = tokens_list;

	while (current)
	{
		t_tokens *token = (t_tokens *)current->content;

		if (token->type_token == WORD)  // Si el token es una palabra
		{
			if (is_builtin(token->str))
				token->type_token = BUILTINS;
		}

		current = current->next;
	}
}

// Función que actualiza el tipo de los tokens después de un pipe

void	update_after_pipe_to_builtin(t_list *tokens_list)
{
	t_list	*current;
	int		after_pipe;  // Flag para saber si es después de un pipe

	current = tokens_list;
	after_pipe = 0;
	while (current)
	{
		t_tokens *token = (t_tokens *)current->content;

		if (token->type_token == PIPE)
			after_pipe = 1;
		else if (after_pipe && token->type_token == WORD)
		{
			if (is_builtin(token->str))
				token->type_token = BUILTINS;
			after_pipe = 0;  // Reset flag
		}
		current = current->next;
	}
}

//**********MAIN FUNCTION***************/
// **Identifica los comandos en la lista de tokens
int	identify_commands(t_list *tokens_list)
{
	t_list      *current;
	t_tokens    *tokens;

	if (!tokens_list)
		return (FALSE);

	current = tokens_list;
	while (current)
	{
		tokens = (t_tokens *)current->content;
		if (tokens->type_token == WORD)
		{
			update_words_to_builtin(tokens_list);
		}
		current = current->next;
	}
	update_after_pipe_to_builtin(tokens_list);
//	t_cmd linked_list_commands = add
	return (TRUE);
}
