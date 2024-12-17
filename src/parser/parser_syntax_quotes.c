
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

int	handle_special_quotes(t_tokens *token)
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

char	*remove_quotes_str(char *str, char c)
{
	int		i;
	int		j;
	int		new_len;
	char	*new_str;

	i = 0;
	new_len = 0;
	while (str[i])
		new_len += (str[i++] != c);
	new_str = (char *)malloc(sizeof(char) * (new_len + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			new_str[j++] = str[i];
		}
		i++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}
