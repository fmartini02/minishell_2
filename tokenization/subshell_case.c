/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:05:37 by francema          #+#    #+#             */
/*   Updated: 2025/05/14 17:08:06 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*subshell_case(t_mini *shell, char *content, size_t *i)
{
	char	*s;

	s = shell->input;
	if (s[*i] == '(' && shell->subshell_flag == 0)
	{
		while (s[*i] && s[*i] != ')')
		{
			(*i)++;
			if (s[*i] == '(')
				return (NULL);
		}
		shell->subshell_flag = 1;
	}
	else if (s[*i] == ')')
	{
		shell->subshell_flag = 0;
		(*i)++;
	}
	else
	{
		content = ft_strjoin_free(content, s + *i);
		(*i)++;
	}
	if (!content)
		return (NULL);
	return (content);
}
