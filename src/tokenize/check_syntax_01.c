#include "../../includes/minishell.h"


// void    check_syntax(char *str)
// {


// }


int count_tokens_in_line(char *str)
{
    int i;
    int count_words;

    i = 0;
    count_words = 0;
    while (str[i] == ' ' && (str[i] >= 9 && str[i] <= 13) && str[i] != '\0')
        i ++;
    while (str[i] != '\0')
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
            i ++;
        if (str[i])
            count_words ++;
        while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] == '\n'))
            i ++;
    }
    return (count_words);
}

/*
typedef enum e_token_type
{
    WORD,           // Representa una palabra o comando
    PIPE,           // Representa el operador de tubería '|'
    REDIR_OUTPUT,   // Representa la redirección de salida '>'
    REDIR_INPUT,    // Representa la redirección de entrada '<'
    CONCAT_OUTPUT,   // Representa la redirección de concatenación '>>'
    NULL_TYPE       // Representa el final de la lista de tokens

}                   t_token_type;
*/

//  CATEGORIZAR CADA TOKEN con la estructura e_token_type
//  cat -n "hello world"
void    categorize_each_token(char **token, struct s_token *list_token) 
{
    int     i;
    size_t  len_token;

    i = 0;
    len_token = 0;
    while (token[i] != NULL)
    {
        while (token[i])
        {
            len_token = ft_strlen(token[i]);
            if (len_token == 1)
            {
                // check type of token

            }
            else if (len_token == 2)
            {
                // check type of token
            }
            else if (len_token > 2)
            {

            }
        }
        i ++;
    }
}

//  ls -l | cat -w | < **

int identify_redirecctions_pipes(char *readline)
{
    int     words_in_line;
    char    **clean_line;

    words_in_line = count_words(readline);
    if (words_in_line > 0)
    {
        clean_line = ft_split(readline, ' ');
        //  categorizar cada token con su tipo

    }

}
