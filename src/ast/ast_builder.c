/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 13:28:00 by catalinab         #+#    #+#             */
/*   Updated: 2026/05/20 13:28:00 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Busca el último pipe en la lista de tokens para dividir el árbol.
 * El pipe con menor prioridad debe ser la raíz.
 */
static t_list	*find_last_pipe(t_list *tokens)
{
	t_list		*last_pipe;
	t_list		*curr;
	t_tokens	*token;

	last_pipe = NULL;
	curr = tokens;
	while (curr)
	{
		token = (t_tokens *)curr->content;
		if (token->type_token == PIPE)
			last_pipe = curr;
		curr = curr->next;
	}
	return (last_pipe);
}

/**
 * Crea una matriz de argumentos a partir de los tokens de tipo WORD.
 */
static char	**extract_command_args(t_list *tokens)
{
	int			count;
	t_list		*curr;
	t_tokens	*tk;
	char		**args;
	int			i;

	count = 0;
	curr = tokens;
	while (curr)
	{
		tk = (t_tokens *)curr->content;
		if (tk->type_token == WORD || tk->type_token == BUILTINS || tk->type_token == CMD_EXTERNAL)
			count++;
		curr = curr->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	curr = tokens;
	while (curr)
	{
		tk = (t_tokens *)curr->content;
		if (tk->type_token == WORD || tk->type_token == BUILTINS || tk->type_token == CMD_EXTERNAL)
			args[i++] = ft_strdup(tk->str);
		curr = curr->next;
	}
	args[i] = NULL;
	return (args);
}

/**
 * Procesa un segmento de tokens (sin pipes) para manejar redirecciones.
 * Devuelve el nodo raíz de este segmento (usualmente un NODE_REDIRECT o NODE_COMMAND).
 */
static t_ast_node	*parse_command_segment(t_list *tokens)
{
	t_list		*curr;
	t_tokens	*tk;
	t_tokens	*next_tk;
	t_ast_node	*node;

	node = NULL;
	curr = tokens;
	/* Primero buscamos redirecciones para que queden por encima del comando */
	while (curr)
	{
		tk = (t_tokens *)curr->content;
		if (is_redir(tk))
		{
			if (curr->next)
			{
				next_tk = (t_tokens *)curr->next->content;
				node = create_redir_node(tk->type_token, next_tk->str, node);
			}
		}
		curr = curr->next;
	}
	/* Si no hay redirecciones o después de crearlas, creamos el nodo de comando */
	if (!node)
		return (create_command_node(extract_command_args(tokens)));
	
	/* Si ya había redirecciones, buscamos el comando y lo ponemos en la rama izquierda del último redirect */
	t_ast_node *tmp = node;
	while (tmp->left)
		tmp = tmp->left;
	tmp->left = create_command_node(extract_command_args(tokens));
	return (node);
}

/**
 * Función principal recursiva para construir el AST.
 */
t_ast_node	*build_ast(t_list *tokens)
{
	t_list		*pipe_token;
	t_list		*left_tokens;
	t_ast_node	*node;

	if (!tokens)
		return (NULL);
	pipe_token = find_last_pipe(tokens);
	if (pipe_token)
	{
		/* Dividir la lista: necesitamos una forma de separar tokens_izq y tokens_der */
		/* Nota: En una implementación real, esto requeriría duplicar las listas o usar punteros inicio/fin */
		/* Para este ejemplo, asumimos una lógica de división */
		
		// t_ast_node *left = build_ast(left_part);
		// t_ast_node *right = build_ast(right_part);
		// return (create_pipe_node(left, right));
		
		/* Pseudocódigo de división para C98 */
		return (NULL); // Implementación pendiente de lógica de división de t_list
	}
	return (parse_command_segment(tokens));
}
