/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_join_quotes_stuff.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:46:40 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 17:58:07 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

// gestisce il caso di citazioni vuote, aggiungendo una stringa vuota a res
static bool	handle_empty_quotes(char **res, size_t *i, t_mini *shell)
{
	char	*tmp;

	tmp = ft_strdup("");
	if (!tmp)
		return (ft_fatal_memerr(shell), false);
	*res = ft_strjoin_free(*res, tmp);
	free(tmp);
	if (!*res)
		return (ft_fatal_memerr(shell), false);
	(*i)++;
	return (true);
}

// gestisce le citazioni singole e doppie,
// aggiungendo il contenuto tra le citazioni a res
bool	process_quoted(char **res, size_t *i, char quote, t_mini *shell)
{
	size_t	start;
	char	*s;

	s = shell->input;
	(*i)++;
	if (s[*i] == quote)
		return (handle_empty_quotes(res, i, shell));
	start = *i;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i] != quote)
		return (handle_unclosed_quote(shell, quote));
	(*i)++;
	return (append_partial_str(res, start, *i - start - 1, shell));
}
