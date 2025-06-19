/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:56:01 by francema          #+#    #+#             */
/*   Updated: 2025/06/19 15:40:37 by francema         ###   ########.fr       */
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
	if (s[*i] == '$')// if there is a $ in the string
	{
		if (*i > start)// if there is text before $
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

static char	*double_quotes_utils(t_mini *shell, char *content, size_t *i, char *s)
{
	size_t	start;

	start = *i;
	while (s[*i] && s[*i] != '\"')
	{
		if (s[*i] == '$')
		{
			content = dollar_quotes_case(shell, i, start, content);
			if (!content)
				return (NULL);
		}
		if (s[*i] != '"')
			(*i)++;
	}
	if (s[*i] != '\"')// unmatched quote
	{
		write(2, "ERROR OPEN DOUBLE QUOTE\n", 25);
		return (NULL);
	}
	if (*i > start)//if there is text before closing quote
	{
		content = get_chars_after_symbol(shell, i, start, content);
		if (!content)
			return (NULL);
	}
}

int	double_quotes_case(t_mini *shell, char *content, size_t *i)
{
	t_tok_lst	*node;
	char		*content;

	content = double_quotes_utils(shell, content, i, shell->input);
	if (!content)
		return (EXIT_FAILURE);
	(*i)++;
	node = new_tok_lst(content, DOUBLE_QUOTES, NULL);
	if (!node)
		ft_fatal_memerr(shell);
	add_back_tok_lst(&(shell->tok_input), node);
	if (!shell->tok_input)
		ft_fatal_memerr(shell);
	return (EXIT_SUCCESS);
}
