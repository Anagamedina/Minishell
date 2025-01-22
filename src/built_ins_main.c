
#include "../includes/minishell.h"

void    cases_builtins(t_mini *mini)
{
    t_cmd   *current_command;


    current_command = (t_cmd *)mini->exec->first_cmd->content;

    printf("current_command : %s\n", current_command->cmd);
//    printf("token 02 : %s\n", token_02->cmd);
    if ((ft_strcmp((char *)current_command->cmd, "echo") == 0))
    {
		ft_echo(current_command);
    }

    // if ((ft_strcmp((char *)current_command->cmd, "export") == 0))
    // {
	// 	builtin_export(mini);
    // }
    // else if (ft_strcmp((char *)current_command->cmd, "cd") == 0)
	// {
	// 	printf("enmtra caso cd\n");
	// 	get_current_directory(mini);
	// }
	else
		return ;
}
