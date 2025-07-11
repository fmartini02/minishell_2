/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_tokenize.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:18:02 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 00:24:35 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	add_double_quote_token(t_mini *shell, char *content)
{
	t_tok_lst	*node;

	node = new_tok_lst(content, DOUBLE_QUOTES, NULL);
	if (!node)
		ft_fatal_memerr(shell);
	add_back_tok_lst(&(shell->tok_input), node);
	if (!shell->tok_input)
		ft_fatal_memerr(shell);
	return (EXIT_SUCCESS);
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

	return add_double_quote_token(shell, content);
}

char	*token_join(char *content, t_mini *shell, size_t *i)
{
	char	*tmp;

	tmp = to_join(shell->input, i, shell);
	if (!tmp)
	{
		free(content);
		if (shell->err_print)
			return (NULL);
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
