/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2024/12/17 17:41:02 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPE_H
# define PROTOTYPE_H

# include "../libft/libft.h"
# include "minishell.h"
# include "prototype.h"
# include "macros.h"

typedef struct s_env		t_env;
typedef struct s_tokens		t_tokens;
typedef struct s_cmd		t_cmd;
typedef struct s_mini		t_mini;
typedef struct s_split_data	t_split_data;

//**************ENV************/
t_list		*init_env_list(char **envp);
t_env		*init_empty_env_node(void);
void		print_env_list(t_list *env_list);

//************** ENV_LIST ************/
t_env		*init_struct_env(void);
void		free_env(t_env *env);
t_env		*init_env(char *line);

//************** ENV_LOCALS ************/
int			validate_var_name(const char *line);
int			validate_var_value(const char *line);
char		*get_var_name(char *line);
char		*get_var_value(char *line);
t_list		*create_local_vars_list(char *line, t_list *local_vars_list);

//*************INPUT***********/
char		*read_input(void);
int			check_quotes_line(char *line);
void		parser_tokens(t_mini *mini);

//************** INIT_COMMAND.C ********/

int			is_type_of_operator(t_tokens *token);
t_cmd		*init_command(void);
void		print_list_commands(t_list *cmd_list);
t_cmd		*create_new_command(t_tokens *current_token, int i);
t_list		*add_tokens_to_linked_list_commands(t_list *token_list);
void		contar_numero_argumentos_de_comandos(t_list *token_list, t_cmd *cmd);
void		agregar_argumentos_a_comando(t_cmd **cmd, t_list *token_list);

//************** ERRORS_COMMAND.C ********/

void		free_command(t_cmd *cmd);
void		free_command_list(t_cmd *cmd_list);
// void			check_null_token(t_tokens *token, t_cmd *cmd_list, char *err_message);
int			error_empty_token(t_tokens *token, t_list *cmd_list);
int			error_cmd_creation(t_cmd *cmd, t_list *cmd_list);
int			error_node_creation(t_list *node, t_cmd *cmd, t_list *cmd_list);

//**************BUILTINS-1********/

void		add_env_back(t_env **env_list, t_env *new_node);
void		update_var(char *line, t_list **env_list);
void		only_export(t_list *env_list);
void		init_process_export(t_list *tokens, t_list *env_list);
void		handle_local_or_unknown(t_tokens *first_token, t_list **local_vars);
void		builtin_export(t_mini *mini);
t_env		*find_env_var(t_list *env_list, char *key);

//************ MAIN BUILTINS ********/

void		cases_builtins(t_mini *mini);

//************ INIT_STRUCTUC MINISHELL ********/

t_mini		*init_mini_list(char **envp);
void		print_mini(t_mini *mini);

//************************* BUILTINS-2 ***********************/

//************** builtin_pwd.c ********************/
void		get_current_directory(t_mini *mini);

//************************* TOKENIZE ************************/

//************** TOKEN_LIST.c ********************/

t_tokens	*init_token(char *str, int token_type);
void		print_list_token(t_list *tokens_list);
void		print_list_token_str(t_list *tokens_list);
int			check_lowercase_tokens(t_list *tokens_list);
t_list		*tokenize_list(char **tokens);
t_list		*generate_token_list(char *line);

//************** TOKEN_FREE.c ********************/

int			ft_strcmp(char *s1, char *s2);
char		*ft_strncpy(char *s1, const char *s2, int n);
void		free_split_result(char **out);
void		free_split_result_struct(char **out, int k);
int			copy_word(t_split_data *data);

//************** TOKEN_TYPE.c ********************/

int			set_token_type(char *str);
int			is_builtin_command(const char *str);
void		update_words_to_builtin(t_list *tokens_list);
void		identify_commands(t_list *tokens_list);

//************** TOKEN_UTILS.c ********************/

char		**ft_split_quote(char *str);

//************** PARSER.c ********************/
//
//************** parser_syntax_dollar.c ********************/

char		*remove_quotes_str(char *str, char c);

//************** parser_syntax_quotes.c ********************/

int			handle_single_quote(t_tokens *token);
int			handle_double_quotes(t_tokens *token);
int			handle_special_quotes(t_tokens *token);
char		*remove_d_quote_s_quotes_str(char *str);

//************** parser_syntax_expand.c ********************/
void		handle_dollar_cases(t_tokens *token, t_list *env_list);
//int			check_doble_dollar_single(const char *str);
int			check_backslash_before_dollar(const char *str);
void		handle_tokens(t_tokens *token, t_list *env_list);
int			has_string_before_dollar(const char *str);

//************** parser_not_expand.c ********************/

int			check_doble_dollar_single(const char *str);
int			has_only_one_digit_after_dollar(const char *str);
char		*convert_escape_sequences(const char *str);
int			has_dollar_followed_by_digit(const char *str);

//************** parser_func.c ********************/

void		expand_dollar(t_tokens *token_list, t_list *env_list);

//************** expand_func.c ********************/
void		get_var_from_token(t_tokens *token_list, t_list *env_list);
void		copy_word_to_token(const char *word, char *merged_token, size_t *k);

//************** expand_utils.c ********************/
int			process_token_is_word(const char *str);
char		*replace_dollar_variable_skip_s_quote(char *token_rm_d_quote, t_list *env_list);
void		replace_dollar_variable(char **split_word, t_list *env_list);
char		*ft_strjoin_array(char **split_word);

#endif