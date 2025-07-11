/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:37:42 by francema          #+#    #+#             */
/*   Updated: 2025/07/11 16:34:20 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// stampa messaggio di errore per citazione non chiusa
// e restituisce false per indicare un errore
static bool	handle_unclosed_quote(t_mini *shell, char quote)
{
	ft_putstr_fd("minishell: unclosed ", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd(" quote\n", 2);
	shell->err_print = true;
	return (false);
}

//unisce una sottostringa di s da start a end in res
static bool	append_substr(char **res, size_t start, size_t end, t_mini *shell, bool is_qouted)
{
	char	*tmp;
	char	*s;

	s = shell->input;
	if (is_qouted)
		tmp = ft_substr(s, start, end - start -1);// -1 to exclude the closing quote
	else
		tmp = ft_substr(s, start, end - start);
	if (!tmp)
		return (ft_fatal_memerr(shell), false);
	*res = ft_strjoin_free(*res, tmp);
	if (!*res)
		return (free(tmp), ft_fatal_memerr(shell), false);
	free(tmp);
	return (true);
}

// gestisce il caso di citazioni vuote, aggiungendo una stringa vuota a res
static bool	handle_empty_quotes(char **res, size_t *i, t_mini *shell)
{
	char *tmp = ft_strdup("");
	if (!tmp)
		return (ft_fatal_memerr(shell), false);
	*res = ft_strjoin_free(*res, tmp);
	free(tmp);
	if (!*res)
		return (ft_fatal_memerr(shell), false);
	(*i)++;
	return (true);
}

// gestisce le citazioni singole e doppie, aggiungendo il contenuto tra le citazioni a res
static bool	process_quoted(char **res, size_t *i, char quote, t_mini *shell)
{
	size_t	start;
	char	*s;

	s = shell->input;
	(*i)++; // Skip opening quote
	if (s[*i] == quote)
		return (handle_empty_quotes(res, i, shell));
	start = *i; // Start after opening quote
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i] != quote)
		return (handle_unclosed_quote(shell, quote));
	(*i)++; // Skip closing quote
	return (append_substr(res, start, *i, shell, true));
}

// gestisce il caso in cui non ci sono citazioni, aggiungendo la sottostringa a res
static bool	process_unquoted(char **res, size_t *i, size_t *start, t_mini *shell)
{
	if (*i > *start)
	{
		if (!append_substr(res, *start, *i, shell, false))
			return false;
		*start = *i;
	}
	return true;
}

// unisce le parole per creare i token come la bash
// gestisce le citazioni e le variabili, restituendo una stringa unita
char	*to_join(char *s, size_t *i, t_mini *shell)
{
	char	*res;
	size_t	start;

	res = NULL;
	start = *i;
	while (s[*i] && s[*i] != '<' && s[*i] != '>' && s[*i] != '|' && s[*i] != ' ')
	{
		while (s[*i] && s[*i] != '<' && s[*i] != '>' && s[*i] != '|' && s[*i] != ' '
			&& s[*i] != '\'' && s[*i] != '"')
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
	if (*i > start && !append_substr(&res, start, *i, shell, false))
		return (free(res), NULL);
	return res;
}
