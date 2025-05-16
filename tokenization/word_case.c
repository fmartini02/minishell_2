/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:44:03 by francema          #+#    #+#             */
/*   Updated: 2025/05/16 15:52:54 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_quote_or_dollar(char c)
{
	if (c == '\'' || c == '"' || c == '$')
		return (true);
	return (false);
}

static bool	is_special_char(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&' || c == '(' || c == ')')
		return (true);
	return (false);
}

static bool	safe_append(char **content, char *s, size_t *i, int *len)
{
	char	*tmp;

	tmp = NULL;
	if (*len > 0)
	{
		tmp = ft_substr(s, *i, *len);
		if (!tmp)
			return (false);
		*content = ft_strjoin_free(*content, tmp);
		free(tmp);
		if (!*content)
			return (false);
		*i += *len;
		*len = 0;
	}
	return (true);
}

static bool	 word_case_helper(t_mini *shell, char c, char **content, size_t *i)
{
	char	*tmp;

	if (c == '\'')
	{
		tmp = single_quotes_case(shell, *content, i);
		*content = ft_strdup(tmp);
		if (!content)
			return (false);
	}
	else if (c == '"')
	{
		tmp = double_quotes_case(shell, *content, i);
		*content = ft_strdup(tmp);
		if (!content)
			return (false);
	}
	else if (c == '$')
	{
		tmp = tok_dollar_case(shell, i, *content);
		*content = ft_strdup(tmp);
		if (!content)
			return (false);
	}
	return (true);
}

char	*word_case(t_mini *shell, char *content, size_t *i)
{
	char	*s;
	int		len;
	char	c;

	s = shell->input;
	len = 0;
	while (s[*i + len]
		&& !is_quote_or_dollar(s[*i + len]) && !is_special_char(s[*i + len])
		&& s[*i + len] != '\n')
		len++;
	if (!safe_append(&content, s, i, &len))
		return (NULL);
	c = s[*i + len];// check next char
	if (!word_case_helper(shell, c, &content, i))
		return (NULL);
	return (content);
}
