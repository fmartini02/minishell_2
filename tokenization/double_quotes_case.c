/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:56:01 by francema          #+#    #+#             */
/*   Updated: 2025/07/08 22:35:17 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_chars_after_symbol(t_mini *shell, size_t *i, size_t start,
	char *content)
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

static char	*double_quotes_utils(t_mini *shell, char *content, size_t *i,
	char *s)
{
	size_t	start;

	start = 0;
	if (s[*i] == '"' && s[*i + 1] == '"')
		return ((*i)++, ft_strdup(""));
	if (s[*i] == '"' && s[*i +1] ==' ')
	{
		start = ft_skip_spaces(s, *i + 1);
		if (s[start] == '"')
			return (*i = start + 2, ft_strdup(""));
	}
	if ((s[*i] == '"' && !s[*i + 1]))
		return ((*i)++, NULL);
	start = ++(*i);// to skip the opening quote
	while (s[*i] && s[*i] != '"')
			(*i)++;
	if (*i > start)
	{
		content = get_chars_after_symbol(shell, i, start, content);
		if (!content)
			return (NULL);
		*i += 1; // to skip the closing quote
	}
	return (content);
}

char	*token_join(char *content, t_mini *shell, size_t *i)
{
	char	*tmp;

	tmp = to_join(shell->input, i, shell);
	if (!tmp)
	{
		free(content);
		ft_fatal_memerr(shell);
	}
	content = ft_strjoin_free(content, tmp);
	if (!content)
	{
		free(tmp);
		ft_fatal_memerr(shell);
	}
	free(tmp);
	return (content);
}

int	double_quotes_case(t_mini *shell, char *content, size_t *i)
{
	t_tok_lst	*node;
	char		*s;

	s = shell->input;
	content = double_quotes_utils(shell, content, i, shell->input);
	if (content[0] == '\0')
	{
		node = new_tok_lst(content, DOUBLE_QUOTES, NULL);
		if (!node)
			ft_fatal_memerr(shell);
		add_back_tok_lst(&(shell->tok_input), node);
		if (!shell->tok_input)
			ft_fatal_memerr(shell);
		return ((*i)++, EXIT_SUCCESS);
	}
	if (!content)
		return (EXIT_FAILURE);
	if (s[*i] && s[*i] != '<' && s[*i] != '>' && s[*i] != '|' && s[*i] != ' ')
		content = token_join(content, shell, i);
	if (content[0] == '\0')
		return (free(content), EXIT_SUCCESS);
	node = new_tok_lst(content, DOUBLE_QUOTES, NULL);
	if (!node)
		ft_fatal_memerr(shell);
	add_back_tok_lst(&(shell->tok_input), node);
	if (!shell->tok_input)
		ft_fatal_memerr(shell);
	return (EXIT_SUCCESS);
}
