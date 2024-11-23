#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include "../libft/libft.h"
# include "minishell.h"
# include "macros.h"

typedef struct s_env t_env;
typedef struct s_tokens t_tokens;
typedef struct s_cmd t_cmd;

//**************ENV************/
t_env			*init_env_list(char **envp);
t_env			*get_env(char **envp);
void			print_env_list(t_env *env_list);

//************** ENV_LIST ************/
t_env			*init_struct_env(void);
t_env			*create_local_vars_list(char *line);
void			free_env_list(t_env *head);
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

//************** INIT_COMMAND.C ********/

int				is_type_of_operator(t_tokens *token);
t_cmd			*init_command(void);
void			print_list_commands(t_list *cmd_list);
t_cmd			*create_new_command(t_tokens *current_token, int i);
t_list			*add_tokens_to_linked_list_commands(t_list *token_list);

//************** ERRORS_COMMAND.C ********/
void			free_command(t_cmd *cmd);
void			free_command_list(t_cmd *cmd_list);
void			check_null_token(t_tokens *token, t_cmd *cmd_list, char *err_message);

int				error_empty_token(t_tokens *token, t_list *cmd_list);
int				error_cmd_creation(t_cmd *cmd, t_list *cmd_list);
int				error_node_creation(t_list *node, t_cmd *cmd, t_list *cmd_list);
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