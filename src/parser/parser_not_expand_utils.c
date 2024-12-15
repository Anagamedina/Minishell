#include "../../includes/minishell.h"

/**
 * check if the next character is a single quote like $'hello
 * echo "'$USER'"
 */
int	check_dollar_after_single_quote(const char *str)  //$'..'
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
				return (1);
		}
		i++;
	}
	return (0);
}

/**
 * check if the previous character is a backslash like \\$hello
 * return TRUE or FALSE
 * echo "\$aaa
 */
int	check_backslash_before_dollar(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == DOLLAR_SIGN)
		{
			if (i > 0 && str[i - 1] == BACKSLASH)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int	has_only_one_digit_after_dollar(const char *str)
{
	int len;

	len = (int) ft_strlen(str);
	return (len == 2 && str[0] == DOLLAR_SIGN \
		&& str[1] >= '0' && str[1] <= '9');
}

/**
 * Checks if the token starts with `$` followed by a digit
 * and additional characters.
 */

int	is_digit_and_more_after_dollar(const char *str)
{
	return (str[0] == '$' && ft_isdigit(str[1]) == 1 && str[2] != '\0');
}

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
	int 	len;

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

int	has_string_before_dollar(const char *str)
{
	int i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == DOLLAR_SIGN)
		{
			j = i - 1;
			if ((str[j] >= 'A' && str[j] <= 'Z') || (str[j] >= 'a' && str[j] <= 'z'))
			{
				return (1);
			}
		}
		i++;
	}
	return (0);
}