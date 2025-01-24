

#include "../../includes/minishell.h"




















/*int	has_dollar_between_double_and_single_quotes(const char *str)
{
	int i;
	int condition01;
	int condition02;
	int len;

	len = (int) ft_strlen(str);

	condition01 = str[0] == D_QUOTE && str[len - 1] == D_QUOTE;
	condition02 = FALSE;

	i = 1;
//	" $ '    '   "  --> FALSE
	while (str[i] != '\0')
	{
		if (str[i] == DOLLAR_SIGN)
			condition02 = TRUE;
		if (str[i] == S_QUOTE && condition02)
			return (FALSE);
		i++;
	}
	if (condition01)
		return (TRUE);
	return (FALSE);

}


int	handle_special_balanced_dquotes(t_tokens *token)
{
	int	i;
	int	has_dollar;
	int	count_d_quotes;

	if (!token || token->str[0] != D_QUOTE || token->str[token->length - 1] != D_QUOTE)
		return (FALSE);

	has_dollar = FALSE;
	count_d_quotes = 0;

	i = 0;
	while (token->str[i] != '\0' && token->str[i] >= 31 && token->str[i] <= 126)
	{
		if (token->str[i] == D_QUOTE)
			count_d_quotes ++;
		else if (token->str[i] == DOLLAR_SIGN)
			has_dollar = TRUE;
		else if (token->str[i] == S_QUOTE && (i == 0 || token->str[i - 1] != '\\'))
		{
			if (count_d_quotes % 2 != 0 && has_dollar == FALSE)
				return (FALSE);
		}
		i ++;
	}
	return (TRUE);
}

int	handle_dollar_with_space_single(t_tokens *token)
{
	char	*temp;

	temp = remove_quotes_str(token->str, D_QUOTE);
	token->str = ft_strdup(temp);
	free(temp);
	if (!token->str)
	{
		perror("error: ft_strdup failed");
		return (FALSE);
	}
	return (TRUE);
}


// int	has_even_double_quotes(t_tokens *token)
// {
// 	if (!token || !token->str)
// 		return (FALSE);

// 	if (token->str[0] == D_QUOTE && token->str[token->length - 1] == D_QUOTE)
// 		return (TRUE);
// 	return (FALSE);
// }



int	handle_str_trim_before_dollar(t_tokens *token)
{
	char	*temp;
	char	*substring_str;
	char	*dollar_pos;

	temp = remove_quotes_str(token->str, D_QUOTE);
	if (!temp)
	{
		perror("error: remove_quotes_str failed");
		return (FALSE);
	}
	free(token->str);
	token->str = ft_strdup(temp);
	free(temp);

	printf("token->str: [%s]\n", token->str);

	dollar_pos = ft_strchr(token->str, DOLLAR_SIGN);
	if (dollar_pos)
	{
		substring_str = ft_substr(token->str, 0, dollar_pos - token->str);
		printf("substring_str: [%s]\n", substring_str);
		if (!substring_str)
		{
			perror("Error: ft_substr failed");
			free(token->str);
			return (FALSE);
		}
		free(token->str);
		token->str = ft_strdup(substring_str);
		free(substring_str);
	}
	printf("token->str after trim: [%s]\n", token->str);
	return (TRUE);
}*/