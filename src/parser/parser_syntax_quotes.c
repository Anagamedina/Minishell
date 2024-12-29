
#include "../../includes/minishell.h"

int	handle_double_quotes(t_tokens *token)
{
	if (token->str[0] == D_QUOTE && token->str[token->length - 1] == D_QUOTE)
		return (TRUE);
	return (FALSE);
}

int	handle_single_quote(t_tokens *token)
{
	if (token->str[0] == S_QUOTE && token->str[token->length - 1] == S_QUOTE)
		return (TRUE);
	return (FALSE);
}

int	handle_special_quotes(t_tokens *token) // " '
{
	if (token->str[0] == D_QUOTE \
		&& token->str[token->length - 1] == D_QUOTE \
		&& token->str[1] == S_QUOTE \
		&& token->str[token->length - 2] == S_QUOTE)
	{
		return (TRUE);
	}
	return (FALSE);
}


// TODO: Revisar esta función y terminarla
/**
 * 
 */

char	*remove_quotes_str(char *str, char c)
{
	int		i;
	int		j;
	int		new_len;
	char	*new_str;

	i = 0;
	new_len = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && str[i] == '\\' && (check_special_c(str[i]) == TRUE) && (str[i] >= 32 && str[i] <= 126))
		{
			new_len ++;
			i ++;
		}
		else if (str[i] != c && (check_special_c(str[i]) == TRUE) && (str[i] >= 32 && str[i] <= 126))
		{
			new_len ++;
			i ++;
		}
		else
			i++;
	}
	printf("new_len: %d\n", new_len);

	new_str = (char *)malloc(sizeof(char) * (new_len + 1));

	if (new_str == NULL)
		return (NULL);

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		// if (str[i] != c && str[i] == '\\' && (str[i] >= 32 && str[i] <= 126))
		if (str[i] != c && str[i] == '\\' && (check_special_c(str[i]) == TRUE) && (str[i] >= 32 && str[i] <= 126))
		{
			new_str[j] = '\\';
			i++;
			j++;
		}
		else if (str[i] != c && (check_special_c(str[i]) == TRUE) && (str[i] >= 32 && str[i] <= 126))
		// if (str[i] != c && (str[i] >= 32 && str[i] <= 126))
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
		else
			i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*remove_d_quote_s_quotes_str(char *str)
{
	char	*rm_d_quote;
	char	*rm_s_quote;
	char	*result;

	rm_d_quote = remove_quotes_str(str, D_QUOTE);
	if (rm_d_quote == NULL)
		return (NULL);

	rm_s_quote = remove_quotes_str(rm_d_quote, S_QUOTE);
	if (rm_s_quote == NULL)
		return (NULL);
	result = ft_strdup(rm_s_quote);
	if (result == NULL)
		return (NULL);
	return (result);
}
