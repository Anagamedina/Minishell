//
// Created by daruuu on 12/1/24.
//
#include "../../includes/minishell.h"

/**
 * check if the next character is a single quote like $'hello
 * echo "'$USER'"
 */
int	check_dollar_after_single_quote(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '\'')
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
				return (1);
		}
		i++;
	}
	return (0);
}

int	has_only_one_digit_after_dollar(const char *str)
{
	int len;

	len = (int) ft_strlen(str);
	return (len == 2 && str[0] == '$' && str[1] >= '0' && str[1] <= '9');
}

/**
 * Calculates the length of a string after removing $<digit> patterns.
 * @param str Input string.
 * @return Length of the new string.
 */
/*
int	calculate_new_length(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] == '$' && str[i + 1] && ft_isdigit(str[i + 1])))
			len++;
		else
			i++;
		i++;
	}
	return (len);
}
*/

/**
 * update the string using malloc
 * @example echo $12345	->	2345
 */
/*
char	*remove_dollar_and_digit(char *str)
{
	int		i;
	int		len;
	char	*result;

	len = calculate_new_length(str);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] && ft_isdigit(str[i + 1]))
			i += 2;
		else
			result[len++] = str[i++];
	}
	result[len] = '\0';
	return (result);
}
*/

/**
 * check if the next character is a single quote like $'hello
 * echo "'$USER'"
 * check backslash before		\\$
 * check single quote after		$'...'
 * llamamos a expand dollar
 */
/************ MAIN FUNCTION *************/

void	handle_dollar_cases(t_tokens *token, t_list *env_list)
{
	char	*temp;

/*
	> echo \$USER
	$USER
*/
	if (check_backslash_before_dollar(token->str) == 1)
	{
		//	TODO: Ana
		printf("backslash before \\$\n");
		printf("token->str: [%s] con id: [%i]\n", token->str, token->id_token);
	}
	else if (check_dollar_after_single_quote(token->str) == 1)
	{
		//	TODO: Ana
		printf("single quote after $\ntoken->str: [%s] con id: [%i]\n", token->str, token->id_token);
	}
	else if (has_only_one_digit_after_dollar(token->str) == 1)
	{
		//	TODO: daru si encuentra un digit entre aqui:	$1
		token->str = ft_strdup("");
	}
/*
	else if (has_only_one_digit_after_dollar(token->str) == 0)
	{
		temp = ft_strdup(token->str + 2);
		free(token->str);
		token->str = ft_strdup(temp);
	}
*/
	else
	{
		printf("call function to expand variable\n");
		printf("token->str: [%s] con id: [%i]\n", token->str, token->id_token);
		expand_dollar(token, env_list);
	}
}
