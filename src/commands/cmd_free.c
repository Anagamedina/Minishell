/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:37:04 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/04 01:04:56 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_command(t_cmd *cmd)
{
    if (!cmd)
        return;
    if (cmd->cmd)
        free(cmd->cmd);
    if (cmd->cmd_path)
        free(cmd->cmd_path);
    if (cmd->cmd_args)
    	free_string_matrix(cmd->cmd_args);
    free(cmd);
}

void	free_cmd_list(t_list **cmd_list)
{
	if (!*cmd_list || !cmd_list)
		return;
	ft_lstclear(cmd_list, (void (*) (void *))free_command);
}
    /*
    t_list *tmp;

    while (cmd_list)
    {
        tmp = cmd_list->next;
    	if (cmd_list->content)
			free_command((t_cmd *)cmd_list->content);
        free(cmd_list);
        cmd_list = tmp;
    }
*/

void	free_exec(t_exec *exec)
{
	// int	i;

    if (!exec)
        return;
    if (exec->first_cmd)
		ft_lstclear(&exec->first_cmd, (void (*)(void *))free_command);
        // free_cmd_list(&exec->first_cmd);
    if (exec->env_vars)
    {
    	free_string_matrix(exec->env_vars);
    }
    if (exec->paths)
    {
		free_string_matrix(exec->paths);
    }
    /*
    if (exec->pipe_input_fd > 0)
        close(exec->pipe_input_fd);
    if (exec->pipe_output_fd > 0)
        close(exec->pipe_output_fd);
    */
    free(exec);
}

void	free_mini(t_mini *mini)
{
    if (!mini)
        return;

    if (mini->env)
    {
        t_list *tmp;
        while (mini->env)
        {
            tmp = mini->env->next;
            free(((t_env *)mini->env->content)->key);
            free(((t_env *)mini->env->content)->value);
            free(mini->env->content);
            free(mini->env);
            mini->env = tmp;
        }
    }

    if (mini->tokens)
    {
        t_list *tmp;
        while (mini->tokens)
        {
            tmp = mini->tokens->next;
            free(((t_tokens *)mini->tokens->content)->str);
            free(mini->tokens->content);
            free(mini->tokens);
            mini->tokens = tmp;
        }
    }

    if (mini->exec)
        free_exec(mini->exec);

    free(mini);
}






// void	free_command(t_cmd *cmd)
// {
// 	int	i;
//
// 	i = 0;
// 	if (!cmd)
// 		return ;
// 	if (cmd->cmd)
// 		free(cmd->cmd);
// 	if (cmd->cmd_path)
// 		free(cmd->cmd_path);
// 	if (cmd->cmd_args)
// 	{
// 		while (cmd->cmd_args[i] != NULL)
// 		{
// 			free(cmd->cmd_args[i]);
// 			i ++;
// 		}
// 		free(cmd->cmd_args);
// 		cmd->cmd_args = NULL;
// 	}
// 	free(cmd);
// }
//
// // void	free_cmd_list(t_list *cmd_list)
// // {
// // 	t_list	*tmp;
// // 	t_cmd	*cmd;
// //
// // 	while (cmd_list)
// // 	{
// // 		tmp = cmd_list->next;
// // 		if (cmd_list->content)
// // 		{
// // 			cmd = (t_cmd *)cmd_list->content;
// // 			if (cmd)
// // 			{
// // 				if (cmd->cmd)
// // 					free(cmd->cmd);
// // 				if (cmd->cmd_args)
// // 					free_string_matrix(cmd->cmd_args);
// // 				if (cmd->cmd_path)
// // 					free(cmd->cmd_path);
// // 				free(cmd);
// // 			}
// // 		}
// // 		free(cmd_list);
// // 		cmd_list = tmp;
// // 	}
// // }
//
//
// void	free_cmd_list(t_list *cmd_list)
// {
// 	t_list	*tmp;
// 	t_cmd	*cmd;
//
// 	while (cmd_list)
// 	{
// 		tmp = cmd_list->next;
// 		if (cmd_list->content)
// 		{
// 			cmd = (t_cmd *)cmd_list->content;
// 			if (cmd)
// 			{
// 				if (cmd->cmd)
// 				{
// 					free(cmd->cmd);
// 					cmd->cmd = NULL;
// 				}
// 				if (cmd->cmd_args)
// 				{
// 					free_string_matrix(cmd->cmd_args);
// 					cmd->cmd_args = NULL;
// 				}
// 				if (cmd->cmd_path)
// 				{
// 					free(cmd->cmd_path);
// 					cmd->cmd_path = NULL;
// 				}
// 				free(cmd);
// 			}
// 		}
// 		free(cmd_list);
// 		cmd_list = tmp;
// 	}
// }
