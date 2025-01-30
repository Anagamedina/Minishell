#include "../../includes/minishell.h"
//verificar que dos operadores no esten seguidos de un operador > >> <
// int check_repeat_redir(t_tokens *token)
// {
// 	while (token)
// 	{
// 		if (strcmp(token->str, ">>") == 0 || strcmp(token->str, "<") == 0 ||
// 			strcmp(token->str, ">") == 0 || strcmp(token->str, "|") == 0 ||
// 			strcmp(token->str, "2>>") == 0 || strcmp(token->str, "2>") == 0)
// 		{
// 			if (!token->next || is_type_of_operator(token->next))
// 			{
// 				fprintf(stderr, "Error: operador '%s' repetido o mal colocado\n", token->str);
// 				return FALSE;
// 			}
// 		}
// 		token = token->next;
// 	}
// 	return (TRUE);
// }



//**********************MAIN FUNCTION ***************//

// void check_redir_syntax(t_tokens *token)
// {

// 	if (check_repeat_redir(token) == TRUE)
// 		printf("check1 ok\n");
// }





//int check_first_last_redir(t_tokens *token)
//{
	//t_tokens *head = token;

	// Verificar si el primer token es un operador de redirección
//	if ((head))
	//{
		//fprintf(stderr, "Error: operador de redirección al principio de la línea\n");
		//return (FALSE);
	//}

	// Recorrer hasta el último token
	//while (token->next)
		//token = token->next;

	// Verificar si el último token es un operador de redirección
	//if (is_redir_token(token->str))
	//{
		//fprintf(stderr, "Error: operador de redirección al final de la línea\n");
		//return (FALSE);
	//}

	//return (TRUE);
//}

//verificar que despues de un operador > >> >> haya un nombre valido de archivo
//int check_file_name(t_tokens *token)
//{


//}