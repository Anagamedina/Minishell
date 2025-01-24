/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:56:02 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/24 13:46:00 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//----> \$USER
int	handle_backslash_after_dollar(t_tokens *token)
{
	char	*temp;

	temp = remove_quotes_str(token->str, D_QUOTE);
	token->str = ft_strdup(temp + 1);
	if (!token->str)
	{
		perror("error: ft_strdup failed");
		return (FALSE);
	}
	return (TRUE);
}

// caso $'..'---> \t ... SIN COMILLA DOBLES
int	handle_single_quotes_after_dollar(t_tokens *token)
{
	char	*temp;
	char	*processed_str;

	processed_str = remove_quotes_str(token->str, S_QUOTE);
	printf("processed_str: [%s]\n", processed_str);
	if (!processed_str)
	{
		perror("Error: remove_quotes_str failed");
		return (FALSE);
	}
	temp = convert_escape_sequences(processed_str);

	if (!temp)
	{
		perror("Error: convert_escape_sequences failed");
		return (FALSE);
	}
	free(token->str);
	token->str = ft_strdup(temp);
	if (!token->str)
	{
		perror("Error: ft_strdup failed");
		return (FALSE);
	}
	return (TRUE);
}

//*********************************************************************/

int	handle_one_digit_after_dollar(t_tokens *token)
{
	free(token->str);
	token->str = ft_strdup("");
	return (TRUE);
}




int	handle_digit_and_more_after_dollar(t_tokens *token)
{
	char	*temp;

	if (token->str[0] == D_QUOTE && token->str[token->length - 1] == D_QUOTE)
	{
		temp = remove_quotes_str(token->str, D_QUOTE);
		token->str = ft_strdup(temp);
		temp = NULL;
	}
	temp = ft_strdup(token->str + 2);
	if (!temp)
	{
		perror("error: strdup");
		exit(EXIT_FAILURE);
	}
	free(token->str);
	token->str = temp;
	return (TRUE);
}



static void	handle_case_dquote_squote(t_tokens *token, t_list *env_list)
{
	char	*processed_str;
	char	*expanded_str;

	processed_str = remove_quotes_str(token->str, D_QUOTE);
	if (!processed_str)
		return;
	free(token->str);
	token->str = ft_strdup(processed_str);
	free(processed_str);

	expanded_str = replace_dollar_variable_skip_s_quote(token->str, env_list);
	if (!expanded_str)
		return;
	free(token->str);
	token->str = ft_strdup(expanded_str);
	free(expanded_str);
}

static void	handle_consecutive_vars(t_tokens *token, t_list *env_list)
{
	char	*processed_str;
	char	*expanded_str;

	processed_str = remove_quotes_str(token->str, D_QUOTE);
	if (!processed_str)
		return;
	free(token->str);
	token->str = ft_strdup(processed_str);
	free(processed_str);

	token->length = ft_strlen(token->str);
	expanded_str = expand_consecutives_variables(token, env_list);
	if (!expanded_str)
		return;
	free(token->str);
	token->str = ft_strdup(expanded_str);
	free(expanded_str);
}

/**********MAIN FUNCTION*************/

void	handle_dollar_cases(t_tokens *token, t_list *env_list, t_tokens *next_token)
{
	if (check_dquote_dollar_and_squotes(token->str))
		return;

	if (check_dquote_squote_dollar_case(token->str))
	{
		handle_case_dquote_squote(token, env_list);
		return;
	}

	if (handle_no_expand_cases(token, next_token) == 0)
	{
		if (has_consecutives_env_variables_in_token(token))
		{
			handle_consecutive_vars(token, env_list);
			return;
		}
	}
}
