#ifndef PROTOTYPE_H
#define PROTOTYPE_H

# include "macros.h"
# include "minishell.h"


typedef struct s_env t_env;
typedef struct s_tokens t_tokens;

typedef struct t_token_type t_token_type;

//**************ENV************/
t_env			*init_struct_env(void);
t_env			*get_env(char **envp);
void			print_env_list(t_env *env_list);

//*************INPUT***********/
char			*read_input(void);
int 			check_quotes_line(char *line);

//********TOKENIZE*************/
char 			**ft_split_quote(char *str);
t_token_type	set_token_type(char *str);
t_tokens		*init_token(char *str, t_token_type token_type);
t_list			*tokenize_list(char *line);



#endif