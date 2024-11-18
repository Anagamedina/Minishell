#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include "../libft/libft.h"
# include "minishell.h"
# include "macros.h"

typedef struct s_env t_env;
typedef struct s_tokens t_tokens;


//**************ENV************/
t_env			*init_env_list(char **envp);
t_env			*get_env(char **envp);
void			print_env_list(t_env *env_list);

//************** ENV_LIST ************/
t_env			*init_struct_env(void);
t_env	*create_local_vars_list(char *line);
void	free_env_list(t_env *head);

//************** ENV_LOCALS ************/

int				validate_var_name(const char *line);
int				validate_var_value(const char *line);
char			*get_var_name(char *line);
char			*get_var_value(char *line);
void			check_var_local_input(char *line);

//*************INPUT***********/
char			*read_input(void);
int 			check_quotes_line(char *line);

//********TOKENIZE*************/
t_list			*generate_token_list(char *line);
char 			**ft_split_quote(char *str);
t_tokens		*init_token(char *str, int token_type);
int 			set_token_type(char *str);
t_list			*tokenize_list(char **tokens);
void			print_list_token(t_list *tokens_list);


#endif