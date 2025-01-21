//
// Created by daruuu on 12/18/24.
//

//caso  -------> "$'..'" ---> no expande ni tabulacion solo imprime
/*
int	check_d_quote_dollar_s_quote(const char *str)
{
	int i;
	int len_str;

	i = 0;
	len_str = (int) ft_strlen(str);
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i + 1] == S_QUOTE && str[len_str - 1] == S_QUOTE)
				return (TRUE);
		}
		i++;
	}
	return (0);
}
*/
/*
int	check_doble_dollar_space_single(const char *str)
{
	int i;
	int len_str;

	i = 0;
	len_str = (int) ft_strlen(str);
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i + 1] == S_QUOTE && str[len_str - 1] == S_QUOTE)
				return (TRUE);
		}
		i++;
	}
	return (0);
}
 */

/*
void	handle_dollar_cases(t_tokens *token, t_list *env_list)
{
	char	*tmp;

	tmp = NULL;
	//"$'...'" ----> imprime
	if (check_d_quote_dollar_s_quote(token->str))
	{
		tmp = remove_quotes_str(token->str, D_QUOTE);
		token->str = ft_strdup(tmp);
		return ;
	}
	//funcion que detecte el caso raro $'...' ----> \t
	if (check_dollar_simple(token->str)) //	$'..'
	{
		//	"$'...'"
		handle_single_quotes_after_dollar(token);
		//	"$ '...'"

	}
	free(tmp);
	if (!handle_no_expand_cases(token))
		expand_dollar(token, env_list);
}
*/

