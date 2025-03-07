/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:45:45 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/07 19:52:34 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_syntax_error_token(const char *token_str)
{
	write(2, "bash: syntax error near unexpected token `", 42);
	write(2, token_str, ft_strlen(token_str));
	write(2, "'\n", 2);
}
