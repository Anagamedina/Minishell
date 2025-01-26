/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:52:31 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/26 11:58:07 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"


int	calculate_result_size(const char *str)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == BACKSLASH && str[i + 1])
			i ++;
		len++;
		i++;
	}
	return (len);
}

void	process_string(const char *str, char *result)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == BACKSLASH && str[i + 1])
		{
			if (str[i + 1] == 'n')
				result[j++] = '\n';
			else if (str[i + 1] == 't')
				result[j++] = '\t';
			else
				result[j++] = str[i + 1];
			i += 2;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
}


//echo "$'\n..\t'"-> $'USER'
char	*convert_escape_sequences(const char *str)
{
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	len = calculate_result_size(str);
	result = malloc(len + 1);
	if (!result)
	{
		perror("malloc error");
		return (NULL);
	}
	process_string(str, result);
	return (result);
}


//******************MAIN FUCNTION***********************/
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
	printf("temp: [%s]\n", temp);
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