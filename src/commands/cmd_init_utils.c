#include "../../includes/minishell.h"


void	add_redirection(t_cmd *cmd, t_list *current)
{
	t_tokens	*token;
	
	token = (t_tokens *)current->content;
	if (is_redir(token) && cmd && current->next)
		add_redirection_to_cmd(cmd, token, (t_tokens *)current->next->content);
}


t_cmd	*process_command_token(t_tokens *token, char **paths, int *cmd_id)
{
	t_cmd	*new_cmd;

	new_cmd = create_new_command(token, paths);
	if (!new_cmd)
	{
		fprintf(stderr, "Error: Falló la creación del comando '%s'.\n", token->str);
		return (NULL);
	}
	new_cmd->cmd_id = (*cmd_id)++;
	new_cmd->last_cmd = 0;
	return (new_cmd);
}




void	add_command_to_list(t_list **cmd_list, t_tokens *token, char **paths, int *cmd_id)
{
	t_cmd	*cmd;
	t_list	*new_node;

	cmd = process_command_token(token, paths, cmd_id);
	if (!cmd)
		return (free_cmd_list(*cmd_list), (void)NULL);
	new_node = ft_lstnew(cmd);
	if (!new_node)
		return (free_command(cmd), free_cmd_list(*cmd_list), (void)NULL);
	ft_lstadd_back(cmd_list, new_node);
}

void	process_command_args(t_list *current, t_cmd *cmd)
{
	count_args(current, cmd);
	add_args(&cmd, current);
}