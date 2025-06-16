/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:05:37 by francema          #+#    #+#             */
/*   Updated: 2025/06/11 17:21:25 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	subshell_case(t_mini *shell, char *content, size_t *i)
{
	t_tok_lst	*node;
	char		*s;
	size_t		tmp;

	s = shell->input;
	tmp = *i;
	node = NULL;
	content = NULL;
	if (s[tmp] == '(')
	{
		while (s[tmp] && s[tmp] != ')')
		{
			tmp++;
			if (s[tmp] == '(')
			{
				ft_putstr_fd("ERROR: NESTED SUBSHELLS NOT ALLOWED\n", 2);
				return (EXIT_FAILURE);
			}
		}
		content = ft_strdup("(");
		node = new_tok_lst(content, SUBSHELL, NULL);
	}
	else if (s[tmp] == ')')
	{
		content = ft_strdup(")");
		node = new_tok_lst(content, SUBSHELL, NULL);
	}
	if (!node || !content)
	{
		if (content)
			free(content);
		ft_fatal_memerr(shell);
	}
	add_back_tok_lst(&(shell->tok_input), node);
	if (!shell->tok_input)
	{
		free(content);
		ft_fatal_memerr(shell);
	}
	*i += 1;
	return (EXIT_SUCCESS);
}
