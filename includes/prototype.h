#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include "../libft/libft.h"
# include "minishell.h"
# include "macros.h"

typedef struct s_env t_env;
typedef struct s_tokens t_tokens;


//**************ENV************/
t_env			*init_env(char *line);
t_list			*init_env_list(char **envp);

//************** ENV_LOCALS ************/

int				validate_var_name(const char *line);
int				validate_var_value(const char *line);
char			*get_var_name(char *line);
char			*get_var_value(char *line);
void			create_local_var(char *line, t_list **local_vars);
t_env	*create_local_vars_list(char *line);

//*************INPUT***********/
char			*read_input(void);
int 			check_quotes_line(char *line);

//********TOKENIZE*************/
int 			ft_strcmp(char *s1, char *s2);
t_list			*generate_token_list(char *line);
char 			**ft_split_quote(char *str);
t_tokens		*init_token(char *str, int token_type);
int 			set_token_type(char *str);
t_list			*tokenize_list(char **tokens);
int				analize_tokens(t_list *tokens_list);
int				identify_commands(t_list *tokens_list);
void 			update_words_to_builtin(t_list *tokens_list);

//**************PRINT********/
void			print_list_token(t_list *tokens_list);
void			print_env_list(t_env *env_list);


//**************BUILTINS-1********/

t_env	*find_env_var (t_list *env_list, char *key);
void	add_env_back(t_env **env_list, t_env *new_node);
void	export_var(char *line, t_list **env_list);
int		only_export(t_env *env_list);
void	handle_export(t_list **tokens, t_list **env_list);
void	handle_local_or_unknown(t_tokens *first_token, t_list **local_vars);
void	handle_input(t_list **tokens, t_list **env_list, t_list **local_vars);

#endif