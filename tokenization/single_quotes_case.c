/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:36:22 by francema          #+#    #+#             */
/*   Updated: 2025/05/14 17:08:03 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*single_quotes_case(t_mini *shell, char *content, size_t *i)
{
	size_t	start;
	char	*tmp;
	char	*s;

	start = ++(*i); // skip opening quote
	s = shell->input;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (s[*i] != '\'') // unmatched quote
		return (NULL);
	tmp = ft_substr(s, start, *i - start); // extract quoted part
	if (!tmp)
		ft_fatal_memerr(shell);
	content = ft_strjoin_free(content, tmp); // accumulate
	free(tmp);
	if (!content)
		ft_fatal_memerr(shell);
	(*i)++; // skip closing quote
	return (content);
}
