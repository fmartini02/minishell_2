/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_dollar_case.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:13:27 by francema          #+#    #+#             */
/*   Updated: 2025/05/14 17:43:57 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*tok_dollar_case(t_mini *shell, size_t *i, char *content)
{
	char	*tmp;
	char	*s;

	s = shell->input;
	tmp = ft_dollar_case(shell, s, i);
	if (!tmp)
		ft_fatal_memerr(shell);
	content = ft_strjoin_free(content, tmp);
	if (!content)
		ft_fatal_memerr(shell);
	free(tmp);
	return (content);
}
