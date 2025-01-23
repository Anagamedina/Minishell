#include "../../includes/minishell.h"

//archivo : paser_check_quotes_dollar.c

// Caso "$ '...'" -> manejar espacio después del dólar



int	is_dollar_followed_by_squote(const char *str, int i, int len_str)
{
	while (str[i] == ' ')
		i++;
	if (str[i] == S_QUOTE && str[len_str - 2] == S_QUOTE)
		return (TRUE);
	return (FALSE);
}

int	check_dquote_dollar_and_squotes(const char *str)
{
	int	i;
	int	len_str;

	i = 0;
	len_str = (int)ft_strlen(str);
	while (str[i] != '\0')
	{
		if (str[i] == DOLLAR_SIGN)
		{
			i++;
			if (is_dollar_followed_by_squote(str, i, len_str))
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int	check_conditions_dquote_squote(char c, int *condition1, int *condition2)
{
	if (c == S_QUOTE)
		*condition1 = TRUE;
	if (c == DOLLAR_SIGN)
		*condition2 = TRUE;
	return (*condition1 && *condition2);
}

int	check_dquote_squote_dollar_case(char *str)
{
	int	i;
	int	len_str;
	int	condition1;
	int	condition2;

	condition1 = FALSE;
	condition2 = FALSE;
	len_str = (int)ft_strlen(str);
	if (str[0] != D_QUOTE || str[len_str - 1] != D_QUOTE)
		return (FALSE);
	i = 1;
	while (i < len_str - 1)
	{
		while (str[i] == ' ' && i < len_str - 1)
			i++;
		if (check_conditions_dquote_squote(str[i], &condition1, &condition2))
			return (TRUE);
		i++;
	}
	return (FALSE);
}




























/*int	check_dquote_dollar_and_squotes(const char *str)
{
	int i;
	int len_str;

	i = 0;
	len_str = (int) ft_strlen(str);

	while (str[i] != '\0')
	{
		if (str[i] == DOLLAR_SIGN)
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == S_QUOTE && str[len_str - 2] == S_QUOTE)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}


int	check_dquote_squote_dollar_case(char *str)
{
	int	i;
	int	len_str;
	int	condition1;
	int	condition2;

	condition1 = FALSE;
	condition2 = FALSE;
	len_str = (int) ft_strlen(str);

	if (str[0] != D_QUOTE || str[len_str - 1] != D_QUOTE)
		return (FALSE);
	i = 1;

	while (i < len_str - 1)
	{

		while (str[i] == ' ' && i < len_str - 1)
			i ++;
		if (str[i] == S_QUOTE)
			condition1 = TRUE;

		if (str[i] == DOLLAR_SIGN && (i + 1) < len_str - 1 \
			&& str[i + 1] != ' ' && str[i + 1] != '\0')
			condition2 = TRUE;
		if (condition1 && condition2)
			return (TRUE);
		i ++;
	}
	return (FALSE);
}
*/