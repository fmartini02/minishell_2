/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:05:37 by francema          #+#    #+#             */
/*   Updated: 2025/05/27 18:05:41 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*subshell_case(t_mini *shell, char *content, size_t *i)
{
	char	*s;
	size_t	tmp;

	s = shell->input;
	tmp = *i;
	if (s[tmp] == '(' && shell->subshell_flag == 0)
	{
		while (s[tmp] && s[tmp] != ')')
		{
			tmp++;
			if (s[tmp] == '(')
			{
				ft_putstr_fd("ERROR: NESTED SUBSHELLS NOT ALLOWED\n", 2);
				return (NULL);
			}
		}
		content = ft_strjoin_free(content, "(");
		shell->subshell_flag = 1;
	}
	else if (s[tmp] == ')')
	{
		shell->subshell_flag = 0;
		content = ft_strjoin_free(content, ")");
	}
	if (!content)
		ft_fatal_memerr(shell);
	*i += 1;
	return (content);
}
