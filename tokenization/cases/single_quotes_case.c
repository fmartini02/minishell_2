/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:36:22 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 15:48:34 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*single_quotes_utils(t_mini *shell, char *s, size_t *i, char *content)
{
	char	*tmp;
	size_t	start;
	bool	eof;

	tmp = handle_empty_or_unpaired_single_quotes(s, i);
	if (tmp)
		return (tmp);
	eof = is_eof(s, *i);
	start = ++(*i);
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (!validate_single_quote_closure(shell, s, *i))
		return (NULL);
	tmp = extract_single_quote_content(shell, start, *i, eof);
	if (!tmp)
		return (NULL);
	content = ft_strjoin_free(content, tmp);
	free(tmp);
	if (!content)
		ft_fatal_memerr(shell);
	(*i)++;
	return (content);
}

int	single_quotes_case(t_mini *shell, char *content, size_t *i)
{
	char	*s;

	s = shell->input;
	content = single_quotes_utils(shell, s, i, content);
	if (!content)
		return (EXIT_FAILURE);
	if (s[*i] && s[*i] != '<' && s[*i] != '>' && s[*i] != '|' && s[*i] != ' ')
		content = token_join(content, shell, i);
	if (!content)
		return (EXIT_FAILURE);
	return (append_single_quote_token(shell, content));
}
