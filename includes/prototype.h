#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include "../libft/libft.h"
# include "minishell.h"
# include "macros.h"

typedef struct s_env t_env;
typedef struct s_tokens t_tokens;


//**************ENV************/
t_env			*init_struct_env(void);
t_env			*get_env(char **envp);
void			print_env_list(t_env *env_list);

//*************INPUT***********/
char			*read_input(void);
int 			check_quotes_line(char *line);

//********TOKENIZE*************/
char			**tokenize_line(char *line);
char 			**ft_split_quote(char *str);
t_tokens		*init_token(char *str, int token_type);
int 			set_token_type(char *str);
t_list			*tokenize_list(char **tokens);
void			print_list_token(t_list *tokens_list);


#endif