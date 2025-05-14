/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:56:01 by francema          #+#    #+#             */
/*   Updated: 2025/05/14 17:48:05 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_chars_after_symbol(t_mini *shell, size_t *i, size_t start, char *content)
{
	char	*tmp;
	char	*s;

	s = shell->input;
	tmp = ft_substr(s, start, *i - start);
	if (!tmp)
		return (NULL);
	content = ft_strjoin_free(content, tmp);
	free(tmp);
	if (!content)
		return (NULL);
	return (content);
}

char	*dollar_quotes_case(t_mini *shell, size_t *i, size_t start, char *content)
{
	char	*tmp_dollar;
	char	*s;

	tmp_dollar = NULL;
	s = shell->input;
	if (s[*i] == '$') // if there is a $ in the string
	{
		if (*i > start) // if there is text before $
		{
			content = get_chars_after_symbol(shell, i, start, content);
			if (!content)
				ft_fatal_memerr(shell);
		}
		tmp_dollar = ft_dollar_case(shell, s, i);
		if (!tmp_dollar)
			return (NULL);
		content = ft_strjoin_free(content, tmp_dollar);// accumulate
		if (!content)
			return (NULL);
		free(tmp_dollar);
	}
	return (content);
}

char	*double_quotes_case(t_mini *shell, char *content, size_t *i)
{
	size_t	start;
	char	*s;

	start = ++(*i); // skip opening quote
	s = shell->input;
	while (s[*i] && s[*i] != '\"')
	{
		if (s[*i] == '$')
		{
			content = dollar_quotes_case(shell, i, start, content);
			if (!content)
				return (NULL);
		}
		else
			(*i)++;
	}
	if (s[*i] != '\"') // unmatched quote
		return (NULL);
	if (*i > start) // trailing content after last $
	{
		content = get_chars_after_symbol(shell, i, start, content);
		if (!content)
			return (NULL);
	}
	(*i)++;
	return (content);
}
