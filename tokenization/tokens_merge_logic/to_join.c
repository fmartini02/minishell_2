/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:37:42 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 16:16:20 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//unisce una sottostringa di s da start a end in res
bool	append_partial_str(char **res, size_t start, size_t len, t_mini *shell)
{
	char	*tmp;
	char	*s;

	s = shell->input;
	tmp = ft_substr(s, start, len);
	if (!tmp)
		return (ft_fatal_memerr(shell), false);
	*res = ft_strjoin_free(*res, tmp);
	if (!*res)
		return (free(tmp), ft_fatal_memerr(shell), false);
	free(tmp);
	return (true);
}

// static bool	append_quoted_substr(
// 	char **res, size_t start, size_t end, t_mini *shell)
// {
// 	if (end <= start)
// 		return (true);
// 	return (append_partial_str(res, start, end - start - 1, shell));
// }

// gestisce il caso in cui non ci sono citazioni,
// aggiungendo la sottostringa a res
static bool	process_unquoted(
	char **res, size_t *i, size_t *start, t_mini *shell)
{
	if (*i > *start)
	{
		if (!append_partial_str(res, *start, *i - *start, shell))
			return (false);
		*start = *i;
	}
	return (true);
}

static bool	is_word_char(char c)
{
	return (c && c != '<' && c != '>' && c != '|'
		&& c != ' ' && c != '\'' && c != '"');
}

// unisce le parole per creare i token come la bash
// gestisce le citazioni e le variabili, restituendo una stringa unita
char	*to_join(char *s, size_t *i, t_mini *shell)
{
	char	*res;
	size_t	start;

	res = NULL;
	start = *i;
	while (is_word_char(s[*i]))
	{
		while (is_word_char(s[*i]) && s[*i] != '\'' && s[*i] != '"')
			(*i)++;
		if (!process_unquoted(&res, i, &start, shell))
			return (NULL);
		if (s[*i] == '\'' || s[*i] == '"')
		{
			if (!process_quoted(&res, i, s[*i], shell))
				return (free(res), NULL);
			start = *i;
		}
	}
	if (*i > start)
	{
		if (!append_partial_str(&res, start, *i - start, shell))
			return (free(res), NULL);
	}
	return (res);
}
