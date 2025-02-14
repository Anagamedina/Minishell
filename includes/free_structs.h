/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:33:46 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/14 14:40:24 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:11:49 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/31 17:12:58 by  dasalaza        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_STRUCTS_H
# define FREE_STRUCTS_H

void	free_tokens(t_list *tokens);
void	free_env(t_env *env);
void	free_env_array(char **env_array, int allocated);
// void	free_redir(t_redir *redir);
void	free_split_data(t_split_data *split_data);
void	free_cmd(t_cmd *cmd);

void	free_exec(t_exec *exec);
void	free_string_matrix(char **matrix_2d);

void	free_mini(t_mini *mini);

#endif
