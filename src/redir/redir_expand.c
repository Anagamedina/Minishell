/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:07:01 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/07 17:07:04 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* -------------------------------------------------------------------------- */
/*  expand_variables: expande $VAR en una línea según el entorno              */
/* -------------------------------------------------------------------------- */
static	char	*replace_variable(char *expanded_line, \
		char *var_name, char *var_value, int i)
{
	char	*prefix;
	char	*new_line;

	prefix = ft_substr(expanded_line, 0, i);
	new_line = ft_strjoin(prefix, var_value);
	free(prefix);
	prefix = ft_strjoin(new_line, &expanded_line[i + ft_strlen(var_name) + 1]);
	free(new_line);
	return (prefix);
}

char	*process_variable_expansion(char *expanded_line, int *i)
{
	char	*var_name;
	char	*var_value;
	char	*new_line;

	var_name = extract_var_name(&expanded_line[*i + 1]);
	if (!var_name)
		return (expanded_line);
	var_value = getenv(var_name);
	if (var_value)
	{
		new_line = replace_variable(expanded_line, var_name, var_value, *i);
		free(expanded_line);
		expanded_line = new_line;
	}
	free(var_name);
	return (expanded_line);
}

char	*expand_variables(char *line)
{
	char	*expanded_line;
	int		i;

	i = 0;
	expanded_line = ft_strdup(line);
	if (!expanded_line)
		return (NULL);
	while (expanded_line[i])
	{
		if (expanded_line[i] == '$' && (ft_isalnum(expanded_line[i + 1]) || \
					expanded_line[i + 1] == '_'))
			expanded_line = process_variable_expansion(expanded_line, &i);
		i++;
	}
	return (expanded_line);
}
