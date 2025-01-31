

#include "../../includes/minishell.h"

int  	check_file(t_mini *mini, t_tokens *token)
{
	t_list *current = mini->token;

	if (!current || !current->next)
	{
		printf("Error: Redirección de salida sin archivo.\n");
		return (FALSE);
	}
	t_tokens *next_token = (t_tokens *)current->next->content;
	if (next_token->type_token != WORD)
	{
		printf("Error: Redirección debe ir seguida de un archivo.\n");
		return (FALSE);	
	}

	return (TRUE);

}
int parse_redir(t_mini *mini)
{
    t_list *token_list;
    t_tokens *curr_token;

    token_list = mini->token;
    while (token_list != NULL)
    {
        curr_token = (t_tokens *)token_list->content;
        if (token_list->next != NULL)
        {
            t_tokens *next_token = (t_tokens *)token_list->next->content;
            if (curr_token->type_token == REDIR_IN || curr_token->type_token == REDIR_OUT || curr_token->type_token == REDIR_APPEND)
            {
                if (next_token->type_token != WORD)
                {
                    printf("Error: Redirección '%s' debe ir seguida de un archivo.\n", curr_token->str);
                    return (FALSE);
                }
            }
        }
		if (check_repeat_redir(mini->token) == FALSE)
		{
    		printf("Error: Redirecciones consecutivas o mal colocadas.\n");
    		return (FALSE);
		}

        else if (curr_token->type_token == REDIR_IN || curr_token->type_token == REDIR_OUT || curr_token->type_token == REDIR_APPEND)
        {
            printf("Error: Redirección '%s' sin archivo.\n", curr_token->str);
            return (FALSE);
        }
        token_list = token_list->next;  
    }
    return (TRUE);
}
