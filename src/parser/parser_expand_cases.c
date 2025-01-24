/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_cases.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:52:31 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/24 13:22:22 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//archivo: parser_expand_cases.c

int	has_consecutives_env_variables_in_token(t_tokens *token)
{
	int	i;
	int	count_dollar;
	
	if (!token || !token->str)
		return (FALSE);
	
	count_dollar = 0;
	i = 0;

	if (token->str[0] == D_QUOTE)
		i = 1;
	while (token->str[i] != '\0')
	{
		while (token->str[i] == SPACE)
			i ++;
		if (token->str[i] == DOLLAR_SIGN && ft_isalpha(token->str[i + 1]))
		{
			count_dollar ++;
			i ++;
			while (token->str[i] != '\0' && (ft_isalpha(token->str[i]) || token->str[i] == '_'))
				i++;
		}
		else if (token->str[i] == DOLLAR_SIGN && token->str[i + 1] == ' ')
		{
			count_dollar ++;
			i ++;
		}
		else
			i ++;
	}
	if (count_dollar >= 1)
		return (TRUE);
	return (FALSE);
}

static char	*append_result(char *result, char *to_append)
{
	char	*updated;

	updated = ft_strjoin(result, to_append);
	free(result);
	return (updated);
}

static char	*handle_dollar_alone(char *result)
{
	char	*tmp;

	tmp = ft_strdup("$");
	if (!tmp)
		return (NULL);
	result = append_result(result, tmp);
	free(tmp);
	return (result);
}

static char	*expand_variable(char *result, t_list *env_list, const char *var, int len)
{
	char	*tmp;
	char	*expanded_value;

	tmp = ft_substr(var, 0, len);
	if (!tmp)
		return (NULL);
	expanded_value = find_value_in_env(env_list, tmp);
	free(tmp);
	if (expanded_value)
		result = append_result(result, expanded_value);
	return (result);
}

static char	*append_non_dollar_char(char *result, char c)
{
	char	*tmp;

	tmp = ft_substr(&c, 0, 1);
	if (!tmp)
		return (NULL);
	result = append_result(result, tmp);
	free(tmp);
	return (result);
}

char	*expand_consecutives_variables(t_tokens *token, t_list *env_list)
{
	char	*result;
	int		i;
	int		j;

	if (!token || !token->str || !env_list)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (token->str[i] != '\0')
	{
		if (token->str[i] == DOLLAR_SIGN)
		{
			i++;
			if (token->str[i] == '\0' || token->str[i] == SPACE)
			{
				result = handle_dollar_alone(result);
				continue;
			}
			j = i;
			while (token->str[j] && token->str[j] != DOLLAR_SIGN && token->str[j] != SPACE)
				j++;
			result = expand_variable(result, env_list, &token->str[i], j - i);
			i = j;
		}
		else
		{
			result = append_non_dollar_char(result, token->str[i]);
			i++;
		}
	}
	return (result);
}




/**
 * char *expand_consecutives_variables(t_tokens *token, t_list *env_list)
{
    int i = 0, j = 0, len = 0;
    char *tmp = NULL;
    char *find_value = NULL;
    char *result = ft_strdup(""); 
    char *token_updated = NULL;

    if (!token || !token->str || !env_list)
        return (NULL);

    while (token->str[i] != '\0')
    {
        if (token->str[i] == DOLLAR_SIGN)
        {
            i++; // Salta el '$'
            j = i;

            if (token->str[j] == '\0' || token->str[j] == SPACE)
            {
                tmp = ft_strdup("$"); // Agrega el dólar solo al resultado
                token_updated = ft_strjoin(result, tmp);
                free(result);
                free(tmp);
                result = token_updated;
                continue;
            }

            while (token->str[j] != '\0' && token->str[j] != DOLLAR_SIGN && token->str[j] != SPACE)
                j++;

            len = j - i;
            tmp = ft_substr(token->str, i, len); 
			//2)segundo caso devolvemos temp y la usamos en el siguiente caso 
            find_value = find_value_in_env(env_list, tmp);
            free(tmp);

            if (find_value)
            {
                token_updated = ft_strjoin(result, find_value);
                free(result);
                result = token_updated;
            }
          	else	
			{
				i = j;
				continue ;

			}
			i = j; // Salta al final del nombre de la variable
        }
        else
        {	//3)tercer caso si no encontramos un dollar lo que hacemos en agregarlo en la cajita 
            tmp = ft_substr(token->str, i, 1); // Extrae un carácter
            token_updated = ft_strjoin(result, tmp);
            free(result);
            free(tmp);
            result = token_updated;
            i++;
        }
    }

    return (result);
}
 */