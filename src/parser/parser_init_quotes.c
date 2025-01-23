
#include "../../includes/minishell.h"


//archivo : parser_init_quotes.c
int	handle_single_quote(t_tokens *token)
{
	if (token->str[0] == S_QUOTE && token->str[token->length - 1] == S_QUOTE)
		return (TRUE);
	return (FALSE);
}


int	handle_special_quotes(t_tokens *token)
{
	int	i;
	int	has_dollar;
	int	count_d_quotes;

	if (!token || token->str[0] != D_QUOTE || token->str[token->length - 1] != D_QUOTE)
		return (FALSE);

	has_dollar = FALSE;
	count_d_quotes = 0;

	i = 0;
	while (token->str[i] != '\0')
	{
		if (token->str[i] == D_QUOTE)
			count_d_quotes ++;
		else if (token->str[i] == DOLLAR_SIGN)
			has_dollar = TRUE;
		else if (token->str[i] == S_QUOTE)
		{
			if (count_d_quotes % 2 != 0 && has_dollar == FALSE)
				return (TRUE);
			else
				return (FALSE);
		}
		i ++;
	}
	return (FALSE);
}

int	has_even_double_quotes(t_tokens* token)
{
	if (!token || !token->str)
		return (FALSE);

	if (token->str[0] == D_QUOTE && token->str[token->length - 1] == D_QUOTE)
		return (TRUE);
	return (FALSE);
}



//echo $'USER'
int	check_dollar_simple(char *str)
{
	int i;
	int len_str;

	i = 0;
	len_str = (int) ft_strlen(str);
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == S_QUOTE && str[len_str - 1] == S_QUOTE)
				return (TRUE);
		}
		i++;
	}
	return (0);
}