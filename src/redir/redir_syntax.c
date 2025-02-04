#include "../../includes/minishell.h"


int check_repeat_redir(t_list *tokens)
{
    t_list *current = tokens;

    while (current && current->next)
    {
        t_tokens *token = (t_tokens *)current->content;
        t_tokens *next_token = (t_tokens *)current->next->content;
        if (token->type_token == REDIR_IN || token->type_token == REDIR_OUT ||
            token->type_token == REDIR_APPEND || token->type_token == PIPE || \
			token->type_token == DELIMITER)
        {
            if (next_token->type_token == REDIR_IN || next_token->type_token == REDIR_OUT ||
                next_token->type_token == REDIR_APPEND || next_token->type_token == PIPE || \
				next_token->type_token == DELIMITER)
            {
                fprintf(stderr, "Error: operador '%s' repetido o mal colocado antes de '%s'.\n",
                        token->str, next_token->str);
                return FALSE;
            }
        }
        current = current->next;
    }
    return (TRUE);
}