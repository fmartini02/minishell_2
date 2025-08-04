/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:13:21 by francema          #+#    #+#             */
/*   Updated: 2025/08/04 14:35:07 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_eof(char *s, size_t i)
{
	if (i == 0)
		return (false);
	while (i > 0 && s[i] == ' ')
		i--;
	if (i == 0)
		return (false);
	if (s[i] != ' ' && s[i] == '<')
	{
		if (i - 1 > 0 && s[i - 1] == '<')
			return (true);
	}
	return (false);
}

char	*handle_empty_or_unpaired_single_quotes(char *s, size_t *i)
{
	size_t	start;

	if (s[*i] == '\'' && s[*i + 1] == '\'')
		return ((*i) += 2, ft_strdup(""));
	if (s[*i] == '"' && s[*i + 1] == ' ')
	{
		start = ft_skip_spaces(s, *i + 1);
		if (s[start] == '"')
			return (*i = start + 2, ft_strdup(""));
	}
	if (s[*i] == '\'' && !s[*i + 1])
		return ((*i)++, NULL);
	return (NULL);
}

char	*extract_single_quote_content(
	t_mini *shell, size_t start, size_t end, bool eof)
{
	char	*tmp;
	char	*s;

	s = shell->input;
	if (eof)
		tmp = ft_substr(s, start - 1, (end + 2) - start);
	else
		tmp = ft_substr(s, start, end - start);
	if (!tmp)
		ft_fatal_memerr(shell);
	return (tmp);
}

bool	validate_single_quote_closure(t_mini *shell, char *s, size_t i)
{
	(void)shell;
	if (s[i] != '\'')
	{
		ft_putstr_fd("minishell: unclosed single quote\n", 2);
		return (false);
	}
	return (true);
}
