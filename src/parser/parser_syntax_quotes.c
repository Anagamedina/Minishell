
#include "../../includes/minishell.h"

/**
 * Checks if the string in the token starts and ends with single quotes ('').
 *
 * @param token: The token structure containing the string to be checked.
 * @return TRUE (1) or FALSE (0) otherwise.
 */

int	handle_single_quote(t_tokens *token)
{
	if (token->str[0] == S_QUOTE && token->str[token->length - 1] == S_QUOTE)
		return (TRUE);
	return (FALSE);
}

int	has_dollar_between_double_and_single_quotes(const char *str)
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

/**
 * Checks if the string starts and ends with double quotes ("")
 *
 * and contains exactly two single quotes ('') within the double quotes.
 * Spaces between quotes are ignored.
 *
 * @param token: The token structure containing the string to be checked.
 * @return TRUE (1) or FALSE (0) otherwise.
 * ---------------------------------------
 * " ' string ' "
 * asumimos que d_quote y s_quotes estan cerrados
 */

//	TODO:

int	handle_special_quotes(t_tokens *token)
{
	int	i;
	int	has_dollar;
	int	count_d_quotes;
	char	c;

	if (!token || token->str[0] != D_QUOTE || token->str[token->length - 1] != D_QUOTE)
		return (FALSE);

	has_dollar = FALSE;
	count_d_quotes = 0;

	i = 0;
	while (token->str[i] != '\0')
	{
		c = token->str[i];
		if (c == D_QUOTE)
			count_d_quotes++;
		else if (c == DOLLAR_SIGN)
			has_dollar = TRUE;
		else if (c == S_QUOTE)
			break;
		i++;
	}
	// Verificación final: comillas dobles deben ser impares y no debe haber $
	if (count_d_quotes % 2 != 0 && has_dollar == FALSE)
		return (TRUE);
	return (FALSE);
}


/**
 * verifica dquotes sean pares y sin tener un dollar sign entre dquote y squote
 *
 * echo " " ' $USER ' ""
 * echo " "" " ' $USER ' " "" "
 */
int	handle_special_balanced_dquotes(t_tokens *token)
{
	int	i;
	int	has_dollar;
	int	count_d_quotes;
	char	c;

	if (!token || token->str[0] != D_QUOTE || token->str[token->length - 1] != D_QUOTE)
		return (FALSE);

	has_dollar = FALSE;
	count_d_quotes = 0;

	i = 0;
	while (token->str[i] != '\0')
	{
		c = token->str[i];
		if (c == D_QUOTE)
			count_d_quotes++;
		else if (c == DOLLAR_SIGN)
			has_dollar = TRUE;
		else if (c == S_QUOTE)
			break;
		i++;
	}
//	Verificación final: comillas dobles deben ser pares y no debe haber $
	if (count_d_quotes % 2 == 0 && has_dollar == TRUE)
		return (TRUE);
	return (FALSE);
}
/*
int	handle_special_quotes(t_tokens *token)
{
	int	i;
	int has_dollar;
	int count_d_quotes_start;
	int count_s_quotes_start;
	int count_d_quotes_end;
	int count_s_quotes_end;
	char	c;

	has_dollar = FALSE;
	count_d_quotes_start = 0;
	count_s_quotes_start = 0;

	count_d_quotes_end = 0;
	count_s_quotes_end = 0;

	if (!token || token->str[0] != D_QUOTE || token->str[token->length] - 1 != D_QUOTE)
		return (FALSE);

	i = 0;
	int len = (int)token->length;
	while (i < (len / 2))
	{
		c = token->str[i];
//		printf("curr char: [%c]\n", c);
		if (token->str[i] == D_QUOTE)
			count_d_quotes_start ++;
		if (token->str[i] == DOLLAR_SIGN && count_s_quotes_start == 0)
			has_dollar = TRUE;
		if (token->str[i] == S_QUOTE)
			count_s_quotes_start ++;
		if (token->str[i] == S_QUOTE && has_dollar == FALSE)
		{
			return (TRUE);
		}
		i ++;
	}
	i = len - 1;
	while (i >= (len / 2))
	{
		c = token->str[i];
//		printf("curr char: [%c]\n", c);
		if (token->str[i] == D_QUOTE)
			count_d_quotes_end++;
		if (token->str[i] == DOLLAR_SIGN && count_s_quotes_end == 0)
			has_dollar = TRUE;
		if (token->str[i] == S_QUOTE)
			count_s_quotes_end++;
		if (token->str[i] == S_QUOTE && has_dollar == FALSE)
			return (TRUE);
		i --;
	}

	return (FALSE);
}
*/

/*
int	handle_special_quotes(t_tokens *token)
{
	int	i;
	int	has_dollar_between_d_quote_s_quote;
	int	count_d_quotes;

	if (token->str[0] != D_QUOTE || token->str[token->length - 1] != D_QUOTE)
		return (FALSE);
	count_d_quotes = 0;

	i = 1;
	while (i < (int)token->length - 1)
	{
		char c = token->str[i];
		if (token->str[i] == DOLLAR_SIGN)
			has_dollar_between_d_quote_s_quote = TRUE;
		if (token->str[i] == S_QUOTE && has_dollar_between_d_quote_s_quote)
			return (FALSE);
		if (token->str[i] == D_QUOTE)
			count_d_quotes ++;

		i++;
	}
	if (token->str[0] == D_QUOTE && token->str[token->length - 1] == D_QUOTE)
		return (FALSE);
	return (TRUE);
}
*/

/**
 * Checks if the token starts and ends with double quotes ("").
 * Case: " string "
 * Case: "" string ""
 * Case: """ string """
 *
 * @param token: The token structure containing the string to be checked.
 * @return TRUE (1) or FALSE (0) otherwise.
 */

int	has_even_double_quotes(t_tokens *token)
{
	if (!token || !token->str)
		return (FALSE);

	if (token->str[0] == D_QUOTE && token->str[token->length - 1] == D_QUOTE)
		return (TRUE);
	return (FALSE);
}

/**
 * char *remove_quotes_str(char *str, char c)
 * -----------------------------------------
 * Removes all occurrences of the specified quote character (c) from the string.
 *
 * @param str: The input string.
 * @param c: The quote character to be removed (e.g., '"' or '\'').
 * @return A new string with the quotes removed. NULL if memory allocation fails.
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
		if ((str[i] != c && (str[i] >= 31 && str[i] <= 126)) || (check_special_c(str[i]) == TRUE))
		{
			new_len ++;
			i ++;
		}
		else
			i++;
	}

	new_str = (char *) malloc(sizeof(char) * (new_len + 1));
	if (new_str == NULL)
		return (NULL);

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != c  && (str[i] >= 31 && str[i] <= 126)) || (check_special_c(str[i]) == TRUE))
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
		else
			i ++;
	}
	new_str[j] = '\0';
	return (new_str);
}

/**
 * char *remove_d_quote_and_s_quotes_str(char *str)
 * -----------------------------------------------
 * Removes all occurrences of both double quotes (") and single quotes (')
 * from the input string.
 *
 * @param str: The input string.
 * @return A new string with both types of quotes removed. NULL if memory allocation fails.
 */

char	*remove_d_quote_and_s_quotes_str(char *str)
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
