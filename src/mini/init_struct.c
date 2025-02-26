/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:59:09 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/26 19:12:38 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_last_executed_command(t_list **env_list, char *last_cmd)
{
	if (!last_cmd)
		return ;
	// Actualizar la variable `_` con el último comando ejecutado
	set_variable_in_env_list(env_list, "_", last_cmd);
}

void check_pwd_exist_in_env_list(t_list **env_list)
{

}

/**
 *
 * update the level of shell
 * update the value of SHLVL in env_list
 * update the value of PWD in env_list
 * update the value of OLDPWD in env_list si no existe
 * update the value of HOME in env_list
 */
// TODO: refactorizar esta función para que sea más legible

static void	configure_shell_env(t_list** env_list, char *shell_level)
{
	t_list	*new_node;
	int		shlvl;
	char	*new_shlvl;
	char	*current_dir;
	char	*env_value;

	new_node = NULL;
	if (!env_list || !*env_list)
		return ;

	if (!env_variable_exists(*env_list, PWD_ENV))
	{
		current_dir = getcwd(NULL, 0);
		if (!current_dir)
			current_dir = ft_strdup("/");
		new_node = create_new_env_node(PWD_ENV, current_dir);
		if (new_node)
			ft_lstadd_back(env_list, new_node);
		free(current_dir);
	}

	env_value = getenv(PATH_ENV);
	if (!env_variable_exists(*env_list, PATH_ENV) && env_value)
	{
		new_node = create_new_env_node(PATH_ENV, ft_strdup(env_value));
		if (new_node)
			ft_lstadd_back(env_list, new_node);
	}

	env_value = getenv(HOME_ENV);
	if (!env_variable_exists(*env_list, HOME_ENV) && env_value)
	{
		new_node = create_new_env_node(HOME_ENV, ft_strdup(env_value));
		if (new_node)
			ft_lstadd_back(env_list, new_node);
	}

	// Si USER no existe, obtenerlo del sistema
	env_value = getenv("USER");
	if (!env_variable_exists(*env_list, "USER") && env_value)
	{
		new_node = create_new_env_node("USER", ft_strdup(env_value));
		if (new_node)
			ft_lstadd_back(env_list, new_node);
	}

	if (!shell_level || shell_level[0] == '-')
	{
		if (!set_variable_in_env_list(env_list, SHLVL, "0"))
		{
			new_node = create_new_env_node(SHLVL, "0");
			if (new_node)
				ft_lstadd_back(env_list, new_node);
		}
	}
    else
    {
        shlvl = ft_atoi(shell_level);
    	if (shlvl >= 100)
    	{
    		write(2, SHELL_LVL_WARNING, ft_strlen(SHELL_LVL_WARNING));
    		new_shlvl = ft_strdup("1");
    	}
    	else
    		new_shlvl = ft_itoa(shlvl + 1);
    	if (new_shlvl)
    	{
			if (!set_variable_in_env_list(env_list, SHLVL, new_shlvl))
				perror("Error: Failed to update SHLVL");
    		free(new_shlvl);
    	}
    }
}

t_mini	*init_mini_list(char **envp)
{
    t_mini	*minishell;
	char	*shlvl;

    minishell = malloc(sizeof(t_mini));
    if (!minishell)
        return (NULL);
    minishell->bash_lvl = -1;
    minishell->chars_in_line = -1;
    minishell->env = init_env_list(envp);
	minishell->envp_to_array = env_list_to_array(minishell->env);
    if (minishell->env == NULL)
    {
    	free(minishell);
        return (NULL);
    }
    minishell->tokens = NULL;
    minishell->exec = NULL;
    minishell->exit_status = 0;
	shlvl = get_variable_in_env_list(minishell->env, SHLVL);
	configure_shell_env(&minishell->env, shlvl);
    return (minishell);
}

/*
void	print_mini(t_mini *mini)
{
    if (!mini)
    {
		printf("Estructura t_mini no inicializada.\n");
        return;
    }

    printf("=== Información de t_mini ===\n");
    printf("Bash Level: %d\n", mini->bash_lvl);
    printf("Chars in Line: %d\n", mini->chars_in_line);
    //printf("Exit Status: %d\n", mini->exit_status);

    printf("\n--- Variables de Entorno ---\n");
    // if (mini->env)
    //     print_env_list((t_list *)mini->env);
    // else
    //     printf("No hay variables de entorno.\n");
    if (mini->tokens)
        print_list_token((t_list *)mini->tokens);
    else
        printf("No hay tokens.\n");

    printf("\n--- Comandos ---\n");
    if (mini->exec)
        print_list_token((t_list *)mini->exec);
    else
        printf("No hay comandos.\n");
    printf("=== Fin de t_mini ===\n");
}
*/
