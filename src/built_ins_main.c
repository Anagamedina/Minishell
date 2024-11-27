
#include "../includes/minishell.h"

void    cases_builtins(t_mini *mini)
{
    t_cmd   *cmd_01;
    t_cmd   *token_02;

    cmd_01 = (t_cmd *)mini->cmds->content;
    token_02 = (t_cmd *)mini->token->next->content;
    printf("cmd_01 : %s\n", cmd_01->cmd);
    printf("token 02 : %s\n", token_02->cmd);

    if ((ft_strcmp((char *)cmd_01->cmd, "export") == 0))
    {
        printf("entro en export:\n");
		builtin_export(mini);
    }
    else
        return ;

    // if (ft_strcmp((char *)cmd_01, "env") == 0)
    // {
    //     print_mini(mini);
    // }

}
