/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:29:30 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/12 13:29:40 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/*
** Crea e inicializa un nuevo nodo `t_tokens` con la cadena y tipo de token proporcionados.
** - Reserva memoria para el token.
** - Copia el contenido de `str` en el campo `str` del nuevo token.
** - Calcula y asigna la longitud de `str`.
** - Inicializa los punteros `next` y `prev` a NULL.
** Devuelve un puntero al nuevo token, o NULL si falla la asignación de memoria.
*/

t_tokens	*init_token(char *str, int token_type)
{

	t_tokens	*new_token;

	new_token = malloc(sizeof(t_tokens));
	if(!new_token)
		return (NULL);
	new_token->str = ft_strdup(str);
	new_token->type_token = token_type;
	new_token->length = ft_strlen(str);
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}


void	print_list_token(t_list *tokens_list)
{
	t_list	*current = tokens_list;
	t_tokens *token;

	while (current != NULL)
	{
		token = (t_tokens *)current->content;  // Accede a `t_tokens` dentro de `content`
		printf("%s\n", token->str);
		current = current->next;
	}
}




/*
** Toma una línea de entrada y la divide en tokens, creando una lista enlazada de `t_list` donde
** cada nodo contiene un `t_tokens` que representa un token individual.
** - Usa `ft_split_quote` para dividir la línea en tokens.
** - Para cada token, llama a `init_token` para crear un `t_tokens` con su tipo y contenido.
** - Almacena cada `t_tokens` en un nodo `t_list` y los enlaza con `ft_lstadd_back`.
** Devuelve un puntero a la lista de tokens o NULL si falla alguna asignación de memoria.
*/

t_list *tokenize_list(char **tokens)
{
	t_list			*tokens_list = NULL;
	//char 			**tokens;
	t_tokens 		*new_token;
	t_list 			*new_node;
	int 			type;
	int i;

	i = 0;
	//tokens = ft_split_quote(line);
	if(!tokens)
		return (NULL);
	while(tokens[i])
	{
		type = set_token_type(tokens[i]);
		new_token = init_token(tokens[i], type);
		if(!new_token)
		{
			ft_lstclear(&tokens_list, free);
			return (NULL);
		}

		new_node = ft_lstnew(new_token);
		if(!new_node)
		{
			free(new_token);
			ft_lstclear(&tokens_list, free);
			return(NULL);
		}
		ft_lstadd_back(&tokens_list, new_node);
		i++;
	}
	free(tokens);
	return (tokens_list);
}



