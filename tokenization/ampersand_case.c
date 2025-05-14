/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ampersand_case.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:34:06 by francema          #+#    #+#             */
/*   Updated: 2025/05/14 17:07:40 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ampersand_case(t_mini *shell, char *content, size_t *i)
{
	char	*s;

	s = shell->input;
	if (s[*i + 1] == '&')
	{
		content = ft_strdup("&&");
		(*i) += 2;
	}
	else
	{
		content = NULL;
		(*i)++;
	}
	if (!content)
			return (NULL);
	return (content);
}
