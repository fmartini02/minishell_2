/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_case.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:34:06 by francema          #+#    #+#             */
/*   Updated: 2025/05/22 17:58:45 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*and_case(t_mini *shell, char *content, size_t *i)
{
	char	*s;

	s = shell->input;
	if (s[*i + 1] == '&')
	{
		content = ft_strdup("&&");
		if (!content)
			ft_fatal_memerr(shell);
		(*i) += 2;
	}
	else
	{
		content = NULL;
		(*i)++;
	}
	return (content);
}
