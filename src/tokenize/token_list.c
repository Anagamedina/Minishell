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
		printf("%s ", token->str);
		printf("tipo: %d ", token->type_token);
		printf("len: %zu\n", token->length);

		current = current->next;
	}
}

int	analize_tokens(t_list *tokens_list)
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

/* Retorno: Un array de strings,
 * donde cada elemento es un token
 * tokens[0] = "echo";
 * tokens[1] = "hello world"; // Comillas gestionadas como un solo token
tokens[2] = "|";
tokens[5] = ">";
tokens[6] = "output.txt";
tokens[7] = NULL;
*/
/*
 * Analiza una línea de entrada, verificando las comillas, dividiéndola en tokens
 * y creando una lista enlazada con los tokens procesados.
 * Retorna la lista de tokens o NULL si hay un error.
 */

t_list	*generate_token_list(char *line)
{
	char	**tokens;
	t_list 	*tokens_list;

//	if (!check_quotes_line(line))
//		return (NULL);
	tokens_list = NULL;
	tokens = NULL;
	tokens = ft_split_quote(line);	//clean line
	tokens_list = tokenize_list(tokens);	//creamos linked list
/*	if (!(analize_tokens(tokens_list)))
	{
		printf("error analize tokens WORDS\n");
		ft_lstclear(&tokens_list, free);
		return (NULL);
	}*/
	//update_words_to_builtin(tokens_list);
	if(identify_commands(tokens_list) == 0)
	{
		printf("error identify commands\n");
		return (NULL);
	}
	return (tokens_list);
}

/*
** Toma una línea de entrada y la divide en tokens, creando una lista enlazada de `t_list` donde
** cada nodo contiene un `t_tokens` que representa un token individual.
** - Usa `ft_split_quote` para dividir la línea en tokens.
** - Para cada token, llama a `init_token` para crear un `t_tokens` con su tipo y contenido.
** - Almacena cada `t_tokens` en un nodo `t_list` y los enlaza con `ft_lstadd_back`.
** Devuelve un puntero a la lista de tokens o NULL si falla alguna asignación de memoria.
*/

t_list	*tokenize_list(char **tokens)
{
	t_list			*tokens_list = NULL;
	t_tokens 		*new_token;
	t_list 			*new_node;
	int i;

	i = 0;
	if(!tokens)
		return (NULL);
	while (tokens[i])
	{
		new_token = init_token(tokens[i], set_token_type(tokens[i]));
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
