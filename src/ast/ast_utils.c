/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 13:25:00 by catalinab         #+#    #+#             */
/*   Updated: 2026/05/20 13:25:00 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*create_ast_node(t_ast_type type)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->redir_type = -1;
	node->file = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast_node	*create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = create_ast_node(NODE_PIPE);
	if (!node)
		return (NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_ast_node	*create_redir_node(int type, char *file, t_ast_node *left)
{
	t_ast_node	*node;

	node = create_ast_node(NODE_REDIRECT);
	if (!node)
		return (NULL);
	node->redir_type = type;
	node->file = ft_strdup(file);
	if (!node->file)
	{
		free(node);
		return (NULL);
	}
	node->left = left;
	return (node);
}

t_ast_node	*create_command_node(char **args)
{
	t_ast_node	*node;

	node = create_ast_node(NODE_COMMAND);
	if (!node)
		return (NULL);
	node->args = args;
	return (node);
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == NODE_COMMAND && node->args)
		free_string_matrix(node->args);
	if (node->type == NODE_REDIRECT && node->file)
		free(node->file);
	free(node);
}
