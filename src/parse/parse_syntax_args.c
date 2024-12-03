//
// Created by daruuu on 12/1/24.
//
#include "../../includes/minishell.h"

//function auxiliar que verifique sintaxis de VAR $
//		$[a-zA-Z][a-zA-Z0-9]*
// gestionar que el $ siempre al principio del str
static int syntax_var_dollar(char *str)
{

}


//iterar por cada argumento de cada comando y 
// le pasamos una funcion auxiliar de syntaxis
//verificar que contiene un $ 
int	check_dollar_in_token(t_cmd *cmd)
{
	int			i;

	i = 0;
	while (cmd->cmd_args[i]!= '\0')
	{
		if (cmd->cmd_args[i] == '$')
		{
			if (syntax_var_dollar(cmd->cmd_args[i]) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
/**
*
*/

void	check_syntax_dollar(t_mini *mini)
{
	t_tokens	*current_token;
	t_tokens	*token_01;
	int 		j;
	int 		i;

	i = 0;
	j = 0;
	current_token = mini->token->content;
	token_01 = current_token->next;

	if (current_token->type_token == BUILTINS)
	{
		if (token_01->str != NULL && check_dollar_in_token(token_01) == 1) //ECHO $VAR caso 1
		{
			//si te encuentras un comilla simple despues de $ ANULAS EXPANADIR
			//f()check_backslash == false
			expand_dollar(mini, token_01, i); //gestiona la ($')
			token_01 = token_01->next;
		}
		else if (token_01->str != NULL && token_01->str[0] == '"' && token_01->length >= 4) //caso 2
		{
//			iteramos por str par aencontrar comilla simple(')
			while (token_01->str[i] != '\0')
			{
				if (token_01->str[i] == '\\')    //comilla simple
				{
					if (check_dollar_in_token(token_01) == 1)
					{
						//si te encuentras un comilla simple despues de $ ANULAS EXPANADIR
						//f()check_backslash == false
						expand_dollar(mini, token_01, i);
					}
				}
				i ++;
			}
		}
		else if (token_01->str != NULL && token_01->str[0] == 103 &&token_01->length >= 4) //caso 3
		{
//			imprime un dollar
		}

	}
}