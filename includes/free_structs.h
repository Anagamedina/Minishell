/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:21:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/05 20:16:20 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_STRUCTS_H
# define FREE_STRUCTS_H

// free_tokens.c
void	free_tokens_list(t_list **tokens);

//	free_cmd.c
void 		free_cmd_list(t_list **cmd_list);
void		free_command(t_cmd *cmd);
t_cmd		*handle_cmd_error(t_cmd *new);

//	free_redir.c
void	free_redir(t_redir *redir);

void	free_env_node(t_env *env);
void	free_env_array(char **env_array, int allocated);
void	free_cmd(t_cmd *cmd);

// free_exec.c
void	free_exec(t_exec *exec);

// free_split.c
void	free_string_matrix(char **matrix_2d);
void	free_partial_split(char **out, const int k);

// free_mini.c
void	free_mini(t_mini *mini);

#endif
