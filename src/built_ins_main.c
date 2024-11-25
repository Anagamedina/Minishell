
#include "../includes/minishell.h"

void    cases_builtins(t_list *cmd_list, t_list *env_list)
{
    t_cmd   *cmd_tmp;

    cmd_tmp = (t_cmd *)cmd_list->content;

    if (ft_strcmp((char *)cmd_tmp->cmd, "export") == 0)
    {
        init_process_export((t_list *)cmd_tmp, env_list);
    }
    if (ft_strcmp((char *)cmd_tmp->cmd, "env") == 0)
    {

    }

}