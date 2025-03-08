/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:47:46 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/08 01:21:29 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPE_H
# define PROTOTYPE_H

// # include "../libft/libft.h"
# include "minishell.h"

typedef struct s_env		t_env;
typedef struct s_tokens		t_tokens;
typedef struct s_cmd		t_cmd;
typedef struct s_mini		t_mini;
typedef struct s_split_data	t_split_data;
typedef struct s_redir		t_redir;
typedef struct s_exec		t_exec;

//typedef struct s_pipe t_pipe;

//************** INIT_ENV_list ************/

t_env		*create_env_node(char *key_value_variable);
t_env		*init_empty_env_node(void);

//************** ENV.C ************/

int			validate_syntax_name_value(char *new_local_var);
t_list		*init_env_list(char **envp);
int			ft_env(t_list* env_list);

//************** ENV_UTILS_LOCALS.c ************/
int			validate_var_name(const char *line);
int			validate_var_value(const char *line);
char		*get_var_name(const char *line);
char		*get_var_value(char *line);
char		*get_variable_in_env_list(t_list *env_list, char *key_to_find);


//*************INPUT***********/
// char		*read_input(void);
char	*read_input(t_mini *mini);
void		configure_terminal(void);
void		parser_tokens(t_mini *mini);

//**************BUILTINS-1********/

void		print_export(t_list** env_list);

t_env		*find_env_var(t_list *env_list, char *key);

//************** BUILT_IN_export.c********/

int			set_variable_in_env_list(t_list **env_list, char *key, char *new_value);
int			env_variable_exists(t_list *env_list, char *key_to_find);
int			ft_export(t_cmd *curr_cmd, t_mini* mini);

//************ EXPORT_UTILS.C **********/

int			update_env_var_exist(t_list **env_lst, char *name, char *value, int flag);
int			add_new_env_variable(t_list **env, char *var_name, char *var_value);

//************ BUILTINS_PART_ONE_UTILS.C **********/

char	*get_var_name_append(char *arg);
char	*get_var_value_append(char *arg);
char	*ft_strjoin_export(const char *s1, char c, const char *s2);
//************ MAIN BUILTINS ********/
int cases_builtins(t_mini* mini, t_cmd* curr_cmd);

//************ BUILTIN_ECHO.c ************/
char	*expand_exit_status(t_mini *mini, char *str);
// int			ft_echo(t_cmd *cmd);//, t_mini *mini);
int			ft_echo(t_cmd *cmd, t_mini *mini);

//************ BUILTIN_PWD.c ************/
int			ft_pwd(t_mini *mini);

//************ BUILTIN_CD.c ************/
int			ft_cd(t_mini* mini, t_cmd* cmd);
int			ft_cd(t_mini* mini, t_cmd* cmd);

//************ BUILTIN_UNSET.c ************/
int			ft_unset(t_list **env_list, t_cmd *cmd);

//************ BUILTIN_EXIT.c ************/
int 		builtin_exit(t_cmd *cmd, t_mini *mini);
long long 	ft_atoll(const char *str);
void 		error_exit(t_mini *mini);
void		cleanup_and_exit(t_mini* mini, int status);

//************ INIT_STRUCTUC MINISHELL ********/

void		configure_shell_env(t_list** env_list, char *shell_level);
t_mini		*init_mini_list(char **envp);

//************************* BUILTINS-2 ***********************/

//************** builtin_pwd.c ********************/
int ft_pwd(t_mini* mini);

//************************* TOKENIZE ************************/

//************** TOKEN_LIST.c ********************/

t_tokens	*init_token(char *str, int token_type);
void		print_list_token(t_list *tokens_list);
t_list		*convert_tokens_to_list(char **tokens);

//************** TOKEN_FREE.c ********************/

int			ft_strcmp(char *s1, char *s2);
char		*ft_strncpy(char *s1, const char *s2, int n);
char		*ft_strcpy(char *dest, const char *src);
int			copy_word(t_split_data *data);

//************** TOKEN_TYPE.c ********************/

int			set_token_type(char *str);
int			is_builtin_or_external(t_tokens *token);
int			is_special_token(t_tokens *token);

//************** TOKEN_UTILS_SPLIT.c ********************/

void		skip_whitespace(const char *str, int *i);
int			skip_quotes(const char *str, int *i);
int			is_whitespace(char c);
int			is_special_char(char c);
t_list		*generate_token_list(char *line);

//************** TOKEN_UTILS_WORD_COUNT.c ********************/

int			count_words_split(char *str);
int			is_quote(char c);

//************** TOKEN_SPLIT.c ********************/

char		**ft_split_quotes(char *str);

//************** TOKEN_UTILS_QUOTES.c ********************/

char		*remove_consecutive_quotes(char *line);

//************** PARSER.c ********************/

//************** parser_tokens.c ********************/
void		parser_tokens(t_mini *mini);

//************** parser_syntax_dollar.c ********************/

int			check_special_c(char c);
char		*remove_quotes_str(const char *str, char c);
int			handle_special_balanced_dquotes(t_tokens *token);
void		remove_and_replace_quotes(t_tokens *token, char quote_type);
char		*append_non_dollar_char(char *result, char c);
int			is_valid_input(t_tokens *token, t_list *env_list);
char		*handle_dollar_alone(char *result);
char	*expand_variable(char *result, t_list *env_list, \
		const char *var, int len);

//************** parser_syntax_quotes.c ********************/

int			handle_single_quote(t_tokens *token);
int			has_even_double_quotes(t_tokens *token);
int			handle_special_quotes(t_tokens *token);
char		*remove_d_quote_and_s_quotes_str(char *str);

//************** parser_syntax_expand.c ********************/

int			check_dquote_dollar_and_squotes(const char *str);
void		handle_dollar_cases(t_tokens *token, t_list *env_list, t_tokens *next_token);
//int			check_d_quote_dollar_s_quote(const char *str);
int			check_backslash_before_dollar(const char *str);
void		handle_tokens(t_tokens *token, t_list *env_list, t_tokens *next_token);
int			has_string_before_dollar(const char *str);
int			check_dquote_squote_dollar_case(char *str);
int			handle_no_expand_cases(t_tokens *token, t_tokens *next_token);
int			has_consecutives_env_variables_in_token(t_tokens *token);
char		*expand_consecutives_variables(t_tokens *token, t_list *env_list);
int			handle_single_quotes_after_dollar(t_tokens *token);
int			handle_backslash_after_dollar(t_tokens *token);
int			handle_one_digit_after_dollar(t_tokens *token);
int			handle_digit_and_more_after_dollar(t_tokens *token);
int			is_valid_input(t_tokens *token, t_list *env_list);

//************** parser_not_expand.c ********************/

int			check_dollar_and_next_token(char **str, t_tokens *next_token);
int			has_only_one_digit_after_dollar(const char *str);
char		*convert_escape_sequences(const char *str);
int			has_dollar_followed_by_digit(const char *str);

//************** parser_func.c ********************/

//************** EXPAND.c ********************/

//************** expand_vars.c ********************/

// void		expand_dollar(t_tokens *token_list, t_list *env_list);
void		get_var_from_token(t_tokens *token_list, t_list *env_list);

//************** expand_token_utils.c ********************/

char		*extract_var_name(const char *str);
int			update_token_str(t_tokens *token, char **split_word);
char		*get_and_reconstruct_token(char *split_word, const char *var_value, int i);
void		copy_word_to_token(const char *word, char *merged_token, size_t *k);

//************** expand_split.c ********************/

char		**ft_split_new_version(char *str);

//************** expand_merge.c ********************/

char		*ft_strjoin_array(char **split_word);
char		*ft_strjoin_char(char *str, char c);

//************** expand_env.c ********************/

char		*find_value_in_env(t_list *env_list, char *var_name_token);
// void		replace_dollar_variable(char **split_word, t_list *env_list);
char		*replace_dollar_variable_skip_s_quote(char *token_rm_d_quote, t_list *env_list);

//************** INIT_COMMAND.C ********/

int			is_builtin_command(char *cmd);
t_cmd		*init_command(void);
void		print_list_commands(t_list *cmd_list);
t_cmd		*create_new_command(t_tokens *current_token, char **paths);
t_list		*create_cmd_list(t_list *token_list, char **paths);
void		count_args(t_list *token_list, t_cmd *cmd);
void		add_args(t_cmd **cmd, t_list *token_list);
int			add_details_to_cmd_list(t_list *commands_list, t_list *token_list);
void		finalize_cmd_list(t_list *commands_list);
t_cmd		*process_command_token(t_tokens *token, char **paths, int *cmd_id);
void		add_redirection(t_cmd *cmd, t_list *current);
void		add_command_to_list(t_list **cmd_list, t_tokens *token, char **paths, int *cmd_id);
void		process_command_args(t_list *current, t_cmd *cmd);
//************** BUILT_INS_UTILS.C ********/

t_list		*create_new_env_node(char* key, char* value);

//************** ERRORS_COMMAND.C ********/

int			error_empty_token(t_tokens *token, t_list *cmd_list);
int			error_cmd_creation(t_cmd *cmd, t_list *cmd_list);
int			error_node_creation(t_list *node, t_cmd *cmd, t_list *cmd_list);
char 		**get_path(char **env);
char 		*get_cmd_path(t_tokens *token, char **paths);
t_exec 		*init_exec(t_list *env_list);
char		**env_list_to_array(t_list *env_list);
char		*is_cmd_external(t_mini *mini, t_tokens *token);
int			execute_commands(t_mini *mini);
void		execute_external(t_cmd *cmd, char **envp);
t_cmd		*init_command(void);
void		handle_child(t_cmd *curr_cmd, t_mini *mini);

//*************redis**************/

void		update_words_in_tokens(t_mini *mini);
void		parse_redir(t_mini *mini);
int			open_file(char *file, int type);
void		add_redirection_to_cmd(t_cmd *cmd, t_tokens *redir_token, t_tokens *file_token);
int			apply_redirections(t_cmd *cmd);
int			is_redir(t_tokens *token);
t_redir		*init_redirection(t_tokens *token, t_tokens *next_token);
void 		execute_builtin_or_external(t_cmd *curr_cmd, t_mini *mini);
int			handle_output_redirection(t_cmd *cmd, t_redir *curr_redir);
int			handle_input_redirection(t_cmd *cmd, t_redir *curr_redir);
char		*generate_heredoc_filename(int nbr_heredoc);
//*************HEREDOC**************/
int 	heredoc(t_cmd *cmd);
void 	redirect_out(int output_fd);
void 	redirect_in(int input_fd);
int		create_heredoc(t_redir *redir, int nbr_heredoc, int expand_vars);
int		write_heredoc_content(int fd_tmp, char *delimiter, int expand_vars);
char 	*expand_variables(char *line);
void	fork_and_execute(t_cmd *cmd, t_mini *mini, int pipe_fd[2], int *input_fd);
void	wait_children(t_mini *mini);
void	handle_parent(t_cmd *curr_cmd, int *pipe_fd, int *input_fd);
void	setup_fds(t_cmd *curr_cmd, int *pipe_fd, int *input_fd);
int 	check_repeated_redirections(t_list *token_list);
char	**env_list_to_array(t_list *env_list);
//*************SIGNALS**************/
int validate_syntax(t_list *token_list);
int validate_pipes_and_separators(t_list *token_list);
int validate_and_update_words_positions(t_mini *mini);
int check_start_and_end_tokens(t_list *token_list);
int	is_redir_out(t_tokens* token);
int	count_env_variables_ia(char **env);
void	print_syntax_error_token(const char *token_str);
int	validate_and_update_words_positions(t_mini *mini);
int	check_consecutive_operators(t_list *token_list);

//*************signals.c**************/make r
int			setup_signals(int mode);
int			configure_signal_handler(int signal, void (*handler)(int));

void	handle_exit(t_mini *minishell);
int		handle_input(char *input, t_mini *minishell);
void	miniloop(t_mini *minishell);
void	handle_special_cases(t_tokens *token, t_list *env_list, \
		t_tokens *next_token);
void	remove_and_replace_quotes(t_tokens *token, char quote_type);
void	print_command_not_found(const char *cmd);
void	handle_memory_allocation_error(void);
void	handle_env_duplication_error(char **env_array, int index);
#endif
