/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:36:22 by francema          #+#    #+#             */
/*   Updated: 2025/06/19 15:48:41 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*single_quotes_utils(t_mini *shell, char *s, size_t *i, char *content)
{
	size_t		start;
	char		*tmp;

	start = ++(*i); // skip opening quote
	tmp = NULL;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (s[*i] != '\'') // unmatched quote
	{
		write(2, ">\nbash: unexpected EOF while looking for matching `\'", 53);
		write(2, "\'\nbash: syntax error: unexpected end of file\n", 46);
		return (NULL);
	}
	tmp = ft_substr(s, start, *i - start); // extract quoted part
	if (!tmp)
		ft_fatal_memerr(shell);
	content = ft_strjoin_free(content, tmp); // accumulate
	free(tmp);
	if (!content)
		ft_fatal_memerr(shell);
	return (content);
}

int	single_quotes_case(t_mini *shell, char *content, size_t *i)
{
	char		*s;
	t_tok_lst	*node;

	s = shell->input;
	content = single_quotes_utils(shell, s, i, content);// process quoted content
	if (!content)
		return (EXIT_FAILURE);
	(*i)++; // skip closing quote
	node = new_tok_lst(content, SINGLE_QUOTES, NULL); // create token node
	if (!node)
		ft_fatal_memerr(shell);
	add_back_tok_lst(&(shell->tok_input), node); // add to token list
	if (!shell->tok_input)
		ft_fatal_memerr(shell);
	return (EXIT_SUCCESS);
}
