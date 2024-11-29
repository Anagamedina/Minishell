//
// Created by daruuu on 11/18/24.
//

#include "../../includes/minishell.h"

void	get_current_directory(t_mini *mini)
{
	char *current_directory = NULL;
	t_env	*mini_env;
	t_env	*env_var;

	mini_env =(t_env *) &mini->env->content;
	if (mini == NULL || mini->env == NULL)
	{
		fprintf(stderr, "Error: entorno no inicializado\n");
		return ;
	}
	env_var = find_env_var((t_list *) mini_env, "PWD");
	if (env_var)
	{
		current_directory = getcwd(NULL, 0);
		if (!current_directory)
		{
			perror("Error: getting the current directory\n");
			return ;
		}
		env_var->value = current_directory;
//		printf("%s\n", env_var->value);
	}
	printf("%s\n", current_directory);
}