/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:42:02 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/19 12:39:00 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:45:57 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/12 11:21:48 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/06 12:55:18 by  dasalaza        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	unset_variable(t_list **env_list, char *var_name)
{
	t_list	*current;
	t_list	*prev;
	t_env	*env_var;

	if (!env_list || !*env_list || !var_name)
		return;

	current = *env_list;
	prev = NULL;

	while (current)
	{
		env_var = (t_env *) current->content;
		if (ft_strcmp(env_var->key, var_name) == 0)
		{
			if (prev) // No es el primer nodo
				prev->next = current->next;
			else // Es el primer nodo de la lista
				*env_list = current->next;

			// Liberar la memoria del nodo eliminado
			free_env(env_var);
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

void	cases_builtins(t_mini *mini, t_cmd* curr_cmd)
{
	// t_cmd	*curr_cmd
	int		i;

	i = 0;
	// curr_cmd = (t_cmd *)mini->exec->first_cmd->content;

	// env
	if (ft_strcmp(curr_cmd->cmd, "pwd") == 0)
        ft_pwd(mini);
	else if (ft_strcmp(curr_cmd->cmd, "echo") == 0)
		ft_echo(curr_cmd);
	else if (ft_strcmp(curr_cmd->cmd, "export") == 0)
	{
		if (curr_cmd->cmd_args[1] != NULL)
			export_variable(curr_cmd, mini);
		else
			print_export(&mini->env);
	}
	else if (ft_strcmp(curr_cmd->cmd, "unset") == 0)
	{
		i = 0;
		while (curr_cmd->cmd_args[i] != NULL)
		{
			unset_variable(&(mini->env), curr_cmd->cmd_args[i]);
			i ++;
		}
	}
	else if (ft_strcmp(curr_cmd->cmd, "env") == 0)
		print_env_list(mini->env);
	else if (ft_strcmp(curr_cmd->cmd, "cd") == 0)
	{
		ft_cd(mini, curr_cmd);
	}
}

/*
    if ((ft_strcmp((char *)current_command->cmd, "export") == 0))
    {
		builtin_export(mini);
    }
*/

/*
 * ft_cd - Implementa el comando `cd` en Minishell.
 *
 * - `cd` sin argumentos -> cambia a `$HOME`
 * - `cd -` -> cambia a `$OLDPWD` y lo imprime
 * - Si el directorio no existe, muestra un error con `perror()`
 *
 * Parámetros:
 * - `cmd` (t_cmd *): Contiene los argumentos de `cd`.
 * - `mini` (t_mini *): Estructura principal del shell.
 */
/*
void ft_cd(t_cmd *cmd, t_mini *mini)
{
    char *path;
    char *old_pwd;
    char *new_pwd;

    if (!mini || !mini->env)
        return;

    // Si no hay argumentos, usar `HOME`
    if (!cmd->cmd_args[1])
    {
        path = get_variable_in_env_list(mini->env, "HOME");
        if (!path)
        {
            write(2, "cd: HOME not set\n", 17);
            return;
        }
    }
    // Si el argumento es `-`, usar `OLDPWD`
    else if (ft_strcmp(cmd->cmd_args[1], "-") == 0)
    {
        path = get_variable_in_env_list(mini->env, "OLDPWD");
        if (!path)
        {
            write(2, "cd: OLDPWD not set\n", 19);
            return;
        }
        write(1, path, ft_strlen(path));
        write(1, "\n", 1);
    }
    else
        path = cmd->cmd_args[1];

    // Obtener el directorio actual antes de cambiar
    old_pwd = getcwd(NULL, 0);
    if (!old_pwd)
    {
        perror("cd");
        return;
    }

    // Intentar cambiar de directorio
    if (chdir(path) == -1)
    {
        perror("cd");
        free(old_pwd);
        return;
    }

    // Actualizar `OLDPWD`
    update_var_exist("OLDPWD", old_pwd, &(mini->env));

    // Actualizar `PWD`
    new_pwd = getcwd(NULL, 0);
    if (new_pwd)
    {
        update_var_exist("PWD", new_pwd, &(mini->env));
        free(new_pwd);
    }
    free(old_pwd);
}
*/



