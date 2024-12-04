//
// Created by daruuu on 12/1/24.
//
#include "../../includes/minishell.h"

//function auxiliar que verifique sintaxis de VAR $
//		$[a-zA-Z][a-zA-Z0-9]*
// gestionar que el $ siempre al principio del str
static int syntax_var_dollar(char *str)
{
	int i;

	if (!(ft_isalpha(str[0])) || ft_isdigit(str[0]))
		return (FALSE);
	i = 1;
	while (str[i] != '\0')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

//iterar por cada argumento de cada comando y 
// le pasamos una funcion auxiliar de syntaxis
//verificar que contiene un $ 

int	check_dollar_in_args(t_cmd *cmd)
{
	int			i;
	char 		**cmd_current;

	i = 0;
	cmd_current = cmd->cmd_args;
	while (cmd_current[i] != NULL)
	{
		int	valor_token_true_false = syntax_var_dollar(cmd_current[i]);
		if (syntax_var_dollar(cmd_current[i]) == 1)
		{
			printf("**** cmd->args[%d]: [%s] %d\n", i, cmd_current[i], valor_token_true_false);
			// return (1);
		}
		i++;
	}
	return (0);
}

void	check_syntax_dollar(t_mini *mini)
{
	t_tokens	*current_token;
	t_cmd		*cmd_copy;
	int 		j;
	int 		i;

	i = 0;
	j = 0;
	current_token = mini->token->content;
	cmd_copy = mini->cmds->content; //cmd1 

	if (current_token->type_token == BUILTINS) //echo
	{
		if (cmd_copy != NULL && check_dollar_in_args(cmd_copy) == 1) //ECHO $VAR caso 1
		{
			//si te encuentras un comilla simple despues de $ ANULAS EXPANADIR
			//f()check_backslash == false
			// expand_dollar(mini, token_01, i); //gestiona la ($')
			// token_01 = token_01->next;
			printf("comando syntaxis ok\n");
		}
// 		else if (token_01->str != NULL && token_01->str[0] == '"' && token_01->length >= 4) //caso 2
// 		{
// //			iteramos por str par aencontrar comilla simple(')
// 			while (token_01->str[i] != '\0')
// 			{
// 				if (token_01->str[i] == '\\')    //comilla simple
// 				{
// 					if (check_dollar_in_token(token_01) == 1)
// 					{
// 						//si te encuentras un comilla simple despues de $ ANULAS EXPANADIR
// 						//f()check_backslash == false
// 						expand_dollar(mini, token_01, i);
// 					}
// 				}
// 				i ++;
// 			}
// 		}
// 		else if (token_01->str != NULL && token_01->str[0] == 103 &&token_01->length >= 4) //caso 3
// 		{
// //			imprime un dollar
// 		}

	}
}