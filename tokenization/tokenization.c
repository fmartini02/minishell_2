/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:00:22 by francema          #+#    #+#             */
/*   Updated: 2025/05/20 16:01:00 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Restituisce un token applicando anche alcune espansioni $*/
char	*get_tok(t_mini *shell, char *s, size_t *i)
{
	char	*content;

	content = NULL;
	if (s[*i] == '\'')
		content = single_quotes_case(shell, content, i);
	else if (s[*i] == '"')
		content = double_quotes_case(shell, content, i);
	else if (s[*i] == '$')
		content = tok_dollar_case(shell, i, content);
	else if (s[*i] == '*')
		content = wildcard_case(shell, content, i);
	else if (s[*i] == '(' || s[*i] == ')')
		content = subshell_case(shell, content, i);
	else if (s[*i] == '&')
		content = and_case(shell, content, i);
	else if (s[*i] == '|')
		content = pipe_char_case(shell, content, i);
	else if (s[*i] == '<' || s[*i] == '>')
		content = redi_case(shell, content, i);
	else
		content = word_case(shell, content, i);
	if (!content)
		return (NULL);
	return (content);
}

/* Suddivide l'input(shell->input) in una lista di token(shell->tok_input) usando get_tok
Serve per dividere il comando in parole comprensibili alla shell*/
void	tokenize_input(t_mini *shell)
{
	size_t	i;
	char	*s;
	char	*content;
	t_list	*node;

	i = 0;
	s = shell->input;
	i = ft_skip_spaces(s, i);
	shell->tok_input = NULL;
	while (s[i])
	{
		content = get_tok(shell, s, &i);
		if (!content)
			ft_fatal_memerr(shell);
		node = ft_lstnew(content);
		if (!node)
			ft_fatal_memerr(shell);
		ft_lstadd_back(&shell->tok_input, node);
		i = ft_skip_spaces(s, i);
	}
}
