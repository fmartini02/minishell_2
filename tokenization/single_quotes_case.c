/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:36:22 by francema          #+#    #+#             */
/*   Updated: 2025/06/30 19:12:55 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*single_quotes_utils(t_mini *shell, char *s, size_t *i,
	char *content)
{
	size_t		start;
	char		*tmp;

	start = ++(*i);
	tmp = NULL;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (s[*i] != '\'')
	{
		write(2, ">\nminishell: unexpected EOF while looking for matching `\'",
			58);
		write(2, "\'\nminishell: syntax error: unexpected end of file\n", 51);
		return (NULL);
	}
	tmp = ft_substr(s, start, *i - start);
	if (!tmp)
		ft_fatal_memerr(shell);
	content = ft_strjoin_free(content, tmp);
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
	content = single_quotes_utils(shell, s, i, content);
	if (!content)
		return (EXIT_FAILURE);
	(*i)++;
	node = new_tok_lst(content, SINGLE_QUOTES, NULL);
	if (!node)
		ft_fatal_memerr(shell);
	add_back_tok_lst(&(shell->tok_input), node);
	if (!shell->tok_input)
		ft_fatal_memerr(shell);
	return (EXIT_SUCCESS);
}
