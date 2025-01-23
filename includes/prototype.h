/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:18:52 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/23 12:52:46 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2024/12/27 16:00:03 by  dasalaza        ###   ########.fr       */
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

typedef struct s_exec t_exec;

//typedef struct s_pipe t_pipe;

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
int			check_quotes_line(const char *line);
void		get_size_words_with_pivote(const char* line);
void		parser_tokens(t_mini *mini);



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
void		ft_echo(t_cmd *cmd);

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
void print_list_token_str_one_line(t_list *tokens_list);
int			check_lowercase_tokens(t_list *tokens_list);
t_list		*convert_tokens_to_list(char **tokens);
char		*clean_consecutive_quotes(const char *line);
t_list		*generate_token_list(char *line);
t_list		*tokenize_list(char **tokens);
t_list *generate_token_list(char *line);

//************** TOKEN_FREE.c ********************/

int			ft_strcmp(char *s1, char *s2);
char		*ft_strncpy(char *s1, const char *s2, int n);
char		*ft_strcpy(char *dest, const char *src);
void		free_split_result(char **out);
void		free_split_result_struct(char **out, int k);
int			copy_word(t_split_data *data);
void		ft_free_array(char **array);

//************** TOKEN_TYPE.c ********************/

int			set_token_type(char *str);
//void		update_words_to_builtin(t_list *tokens_list);
void identify_commands(t_list *tokens_list, t_mini*exec_info);
//************** TOKEN_UTILS.c ********************/

char		**ft_split_quote(char *str);
char		**ft_split_new_version(char *str);
int			count_words(const char *str);
int			find_matching_quote(const char *str, int start_index, char quote_char);

//************** PARSER.c ********************/
//
//************** parser_syntax_dollar.c ********************/

int			check_special_c(char c);
char		*remove_quotes_str(const char *str, char c);
int			handle_special_balanced_dquotes(t_tokens *token);

//************** parser_syntax_quotes.c ********************/

int			handle_single_quote(t_tokens *token);
int			has_even_double_quotes(t_tokens *token);
int			handle_special_quotes(t_tokens *token);
char		*remove_d_quote_and_s_quotes_str(char *str);

//************** parser_syntax_expand.c ********************/

int			check_dquote_dollar_and_squotes(const char *str);
void		handle_dollar_cases(t_tokens *token, t_list *env_list, t_tokens* next_token);
//int			check_d_quote_dollar_s_quote(const char *str);
int			check_backslash_before_dollar(const char *str);
void		handle_tokens(t_tokens *token, t_list *env_list, t_tokens* next_token);
int			has_string_before_dollar(const char *str);
int			check_dquote_squote_dollar_case(char *str);
int			handle_no_expand_cases(t_tokens *token, t_tokens* next_token);
int			has_consecutives_env_variables_in_token(t_tokens *token);
char		*expand_consecutives_variables(t_tokens *token, t_list *env_list);
int			handle_single_quotes_after_dollar(t_tokens *token);
int			handle_backslash_after_dollar(t_tokens *token);
int			handle_one_digit_after_dollar(t_tokens *token);
int			handle_digit_and_more_after_dollar(t_tokens *token);

//************** parser_not_expand.c ********************/

int			check_dollar_and_next_token(char** str, t_tokens* next_token);
int			has_only_one_digit_after_dollar(const char *str);
char		*convert_escape_sequences(const char *str);
int			has_dollar_followed_by_digit(const char *str);

//************** parser_func.c ********************/

void		expand_dollar(t_tokens *token_list, t_list *env_list);

//************** expand_func.c ********************/
void		get_var_from_token(t_tokens *token_list, t_list *env_list);
void		copy_word_to_token(const char *word, char *merged_token, size_t *k);
char		*extract_var_name(const char *str);
char		*get_and_reconstruct_token(const char *split_word, const char *var_value);
int			has_more_than_one_dollar_without_spaces_in_token(const char *str);

//************** expand_utils.c ********************/
char		*find_value_in_env(t_list *env_list, char *var_name_token);
int			process_token_is_word(const char *str);
char		*replace_dollar_variable_skip_s_quote(char *token_rm_d_quote, t_list *env_list);
void		replace_dollar_variable(char **split_word, t_list *env_list);
char		*ft_strjoin_array(char **split_word);


//************** INIT_COMMAND.C ********/

int			is_type_of_operator(t_tokens *token);
int			is_builtin_command(char *cmd);
t_cmd		*init_command(void);
void		print_list_commands(t_list *cmd_list);
t_cmd 		*create_new_command(t_tokens *current_token, int cmd_id, char **paths);
t_list		*create_cmd_list(t_list *token_list, char **paths);
void		count_args(t_list *token_list, t_cmd *cmd);
void		add_args(t_cmd **cmd, t_list *token_list);
int 		add_details_to_cmd_list(t_list *commands_list, t_list *token_list);

//************** ERRORS_COMMAND.C ********/

void		free_command(t_cmd *cmd);
// void			check_null_token(t_tokens *token, t_cmd *cmd_list, char *err_message);
int			error_empty_token(t_tokens *token, t_list *cmd_list);
int			error_cmd_creation(t_cmd *cmd, t_list *cmd_list);
int			error_node_creation(t_list *node, t_cmd *cmd, t_list *cmd_list);
char 		**get_path(char **env);
// int 		main(int argc, char **argv, char **env);
void 		print_paths(char **paths);
char 		*get_cmd_path(t_tokens *token, char **paths);
void 		free_cmd(t_cmd *cmd);
void 		free_cmd_list(t_list *cmd_list);
void		free_split_result(char **result);
t_exec 		*init_exec(t_list *env_list);
char		**lst_to_arr(t_list *env_list);
int 		is_cmd_external(t_mini *mini, t_tokens *token);
int		execute_commands(t_mini *mini);
void		execute_external(t_cmd *cmd, char **envp);
void 		process_flags(t_cmd *cmd, char *cmd_str);
t_cmd 		*init_command(void);
t_cmd		*handle_cmd_error(t_cmd *new);
//t_pipe		*init_pipe(void);
//t_pipe 		*create_pipe(int is_last);
int 		count_pipes(t_list *token_list);
//void		setup_pipes(t_pipe *pipe_info, int cmd_id);

//*************redis**************/

int 		check_repeat_redir(t_tokens *token);
#endif