/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:00:22 by francema          #+#    #+#             */
/*   Updated: 2025/07/03 19:48:11 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_word_delimiter(char c)
{
	if (c != '\'' && c != '"' && c != '<' && c != '>'
		&& c != '\0' && c != '|' && c != '$' && c != ' ')
		return (false);
	return (true);
}

void	pettish_utils(t_mini *shell, char c, int *return_value, size_t *i)
{
	char	*s;

	s = shell->input;
	if (c == '\'')
		*return_value = single_quotes_case(shell, NULL, i);
	else if (c == '"')
		*return_value = double_quotes_case(shell, NULL, i);
	else if (!is_word_delimiter(c) && c != ' ')
		*return_value = word_case(shell, NULL, i);
	else if (c == '$' && s[*i + 1] == ' ')
		*return_value = word_case(shell, NULL, i);
}

/*gestisce quei token che vanno uniti se non ci sono spazzi con
un focus specifico per il caso <"c"$var"d"> */
static void	pettish_tokens(t_mini *shell, char *s, size_t *i, int *return_value)
{
	t_tok_lst	*curr_tok;
	char		c;

	c = s[*i];
	curr_tok = last_token(shell->tok_input);
	if (curr_tok && (curr_tok->type == DOLLAR || curr_tok->type == DOUBLE_QUOTES
			|| curr_tok->type == SINGLE_QUOTES)
		&& s[(*i) - 1] != ' ')
	{
		*return_value = check_tok_front(shell, i);
		if (*return_value == EXIT_FAILURE)
			return ;
	}
	if (*return_value == EXIT_SUCCESS)
		pettish_utils(shell, c, return_value, i);
	if (s[*i] && s[*i] != ' ')
	{
		if (s[*i] == '$' && s[*i] != ' ')
			*return_value = check_tok_back(shell, i, true);
		else
			*return_value = check_tok_back(shell, i, false);
	}
}

/* Restituisce un token applicando anche alcune espansioni <$var>
e alcuni merge dei token*/
int	get_tok(t_mini *shell, char *s, size_t *i)
{
	char		*content;
	int			return_value;

	content = NULL;
	return_value = EXIT_SUCCESS;
	if (s[*i] == '\'' || s[*i] == '"' || (!is_word_delimiter(s[*i]) && s[*i + 1] == ' '))
		pettish_tokens(shell, s, i, &return_value);
	if (return_value == EXIT_FAILURE)
		return (return_value);
	if (s[*i] == '$')
		return_value = tok_dollar_case(shell, i, content);
	else if (s[*i] == '*')
		return_value = wildcard_case(shell, content, i);
	else if (s[*i] == '(' || s[*i] == ')')
		return_value = subshell_case(shell, content, i);
	else if (s[*i] == '&')
		return_value = and_case(shell, content, i);
	else if (s[*i] == '|')
		return_value = pipe_char_case(shell, content, i);
	else if (s[*i] == '<' || s[*i] == '>')
		return_value = redi_case(shell, content, i);
	return (return_value);
}

/* Suddivide l'input(shell->input) in una lista di token(shell->tok_input)
usando get_tok
Serve per dividere il comando in parole comprensibili alla shell*/
bool	tokenize_input(t_mini *shell)
{
	size_t		i;
	char		*s;
	int			return_value;

	i = 0;
	s = shell->input;
	shell->tok_input = NULL;
	i = ft_skip_spaces(s, i);
	return_value = EXIT_FAILURE;
	while (s[i])
	{
		return_value = get_tok(shell, s, &i);
		if (return_value == EXIT_FAILURE)
			return (false);
		else if (return_value == VAR_NOT_FOUND)
			continue ;
		i = ft_skip_spaces(s, i);
	}
	return (true);
}
