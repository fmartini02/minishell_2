/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:56:01 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 15:47:22 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static char	*handle_empty_quotes(char *s, size_t *i)
{
	size_t	start;

	if (s[*i] == '"' && s[*i + 1] == '"')
		return ((*i) += 2, ft_strdup(""));
	if (s[*i] == '"' && s[*i + 1] == ' ')
	{
		start = ft_skip_spaces(s, *i + 1);
		if (s[start] == '"')
			return (*i = start + 2, ft_strdup(""));
	}
	if (s[*i] == '"' && !s[*i + 1])
		return ((*i)++, NULL);
	return (NULL);
}

static char	*extract_double_quoted_content(
	t_mini *shell, size_t *i, size_t start, bool eof)
{
	char	*content;
	char	*s;

	s = shell->input;
	if (eof)
		content = ft_substr(s, start - 1, (*i + 2) - start);
	else
		content = get_chars_after_symbol(shell, i, start, NULL);
	if (!content)
		return (NULL);
	*i += 1;
	return (content);
}

static char	*double_quotes_utils(
	t_mini *shell, char *content, size_t *i, char *s)
{
	size_t	start;
	bool	eof;
	char	*empty_check;

	empty_check = handle_empty_quotes(s, i);
	if (empty_check || g_sig_code == 130)
		return (empty_check);
	eof = is_eof(s, *i);
	start = ++(*i);
	while (s[*i] && s[*i] != '"')
		(*i)++;
	if (s[*i] != '"')
	{
		ft_putstr_fd("minishell: unclosed double quotes\n", 2);
		return (NULL);
	}
	if (*i > start)
		return (extract_double_quoted_content(shell, i, start, eof));
	return (content);
}

int	double_quotes_case(t_mini *shell, char *content, size_t *i)
{
	char	*s;

	s = shell->input;
	content = double_quotes_utils(shell, content, i, shell->input);
	if (!content)
		return (EXIT_FAILURE);
	if (s[*i] && s[*i] != '<' && s[*i] != '>' && s[*i] != '|' && s[*i] != ' ')
		content = token_join(content, shell, i);
	if (!content)
		return (EXIT_FAILURE);
	return (append_double_wuote_token(shell, content));
}
