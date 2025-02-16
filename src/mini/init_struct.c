/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:59:09 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/12 18:43:27 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:28:10 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/12 10:56:15 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	char	*home_dir;
	char	*user;

	new_node = NULL;
	if (!env_list || !*env_list)
		return ;
	// si OLD PWD no existe, se crea y se agrega a la lista de environment
	if (!check_if_var_name_exist(OLDPWD_ENV, *env_list))
	{
		new_node = create_new_env_node(OLDPWD_ENV, NULL);
		if (new_node)
			ft_lstadd_back(env_list, new_node);
		else
			perror("Error: Failed to create OLDPWD");
	}

	if (!check_if_var_name_exist(PATH_ENV, *env_list))
	{
		new_node = create_new_env_node(ft_strdup("PATH"), ft_strdup("/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/sbin"));
		if (new_node)
			ft_lstadd_back(env_list, new_node);
		else
			perror("Error: Failed to create PATH");
	}

	if (!check_if_var_name_exist(HOME_ENV, *env_list))
	{
		// home = getenv("HOME");
		home_dir = get_variable_in_envlist(*env_list, HOME_ENV);
		if (home_dir)
			home_dir = ft_strdup(home_dir);
		else
		{
			home_dir = getenv("HOME");
			if (home_dir)
				home_dir = ft_strdup(home_dir);
			else
				home_dir = ft_strdup("/home/");
		}
		new_node = create_new_env_node(HOME_ENV, home_dir);
		if (new_node)
			ft_lstadd_back(env_list, new_node);
		else
			perror("Error: Failed to create HOME");
	}

	// Si USER no existe, obtenerlo del sistema
	if (!check_if_var_name_exist("USER", *env_list))
	{
		user = getenv("USER");
		if (!user)
			user = "unknown";
		new_node = create_new_env_node(USER_ENV, ft_strdup(user));
		if (new_node)
			ft_lstadd_back(env_list, new_node);
		else
			perror("Error: Failed to create USER");
	}

	if (!shell_level || shell_level[0] == '-')
	{
		if (!update_var_exist(SHLVL, "0", env_list))
		{
			new_node = create_new_env_node(SHLVL, "0");
			if (new_node)
				ft_lstadd_back(env_list, new_node);
			else
				perror("Error: Failed to create SHLVL=0");
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
			if (!update_var_exist(SHLVL, new_shlvl, env_list))
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
    	// fprintf(stderr, "Error: No se pudo inicializar la lista de variables de entorno.\n");
    	free(minishell);
        return (NULL);
    }
    minishell->tokens = NULL;
    minishell->exec = NULL;
    minishell->exit_status = -1;
	shlvl = get_variable_in_envlist(minishell->env, SHLVL);
	configure_shell_env(&minishell->env, shlvl);
    return (minishell);
}

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
    if (mini->env)
        print_env_list((t_list *)mini->env); 
    else
        printf("No hay variables de entorno.\n");

    // printf("\n--- Tokens ---\n");
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
