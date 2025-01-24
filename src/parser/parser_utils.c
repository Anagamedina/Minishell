

#include "../../includes/minishell.h"



int	check_special_c(char c)
{
	if (c == '=' || c == ' ' || c == '@' || c == '#' || c == '-' || c == '+' \
		|| c == '{' || c == '}' || c == '[' || c == ']' || c == '!' \
		|| c == '~' || c == '?' || c == '%' || c == '^' || c == '=' \
		|| c == '*' || c == '/' || c == '$' || c == ';' || c == ':' \
		|| c == '|' || c == '.' || c == '_' || c == ',')
	{
		return (TRUE);
	}
	return (FALSE);
}


int	has_dollar_with_only_spaces_or_only_dollar(const char* str)
{
	return (
		(str[0] != '\0' && str[0] == '"' && str[1] != '\0' && str[1] == '$' \
		&& str[2] != '\0' && str[2] == ' ') || \
		(str[0] != '\0' && str[0] == '"' && str[1] != '\0' && str[1] == '$'));
}


char	*remove_quotes_str(const char *str, char c)
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


/*

char *remove_quotes_str(const char *str, char c) {
	int i;
	int j;
	int new_len;
	char *new_str;

	i = 0;
	new_len = 0;
	while (str[i] != '\0') {
		if ((str[i] != c && (str[i] >= 31 && str[i] <= 126)) ||
			(check_special_c(str[i]) == TRUE)) {
			new_len++;
			i++;
		} else
			i++;
	}

	new_str = (char *) malloc(sizeof(char) * (new_len + 1));
	if (new_str == NULL)
		return (NULL);
	return (new_str);
}


char	*remove_quotes_str2(const char *str, char c)
{
	int		i;
	int		j;
	char	*new_str;
	i = 0;
	j = 0;

	new_str = remove_quotes_str(str, c);
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


char	*remove_d_quote_and_s_quotes_str(char *str)
{
	char	*rm_d_quote;
	char	*rm_s_quote;
	char	*result;

	rm_d_quote = remove_quotes_str2(str, D_QUOTE);
	if (rm_d_quote == NULL)
		return (NULL);

	rm_s_quote = remove_quotes_str2(rm_d_quote, S_QUOTE);
	if (rm_s_quote == NULL)
		return (NULL);
	result = ft_strdup(rm_s_quote);
	if (result == NULL)
		return (NULL);
	return (result);
}
*/