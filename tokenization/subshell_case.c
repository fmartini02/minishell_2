/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:05:37 by francema          #+#    #+#             */
/*   Updated: 2025/06/19 15:55:27 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	subshell_utils(t_mini *shell, size_t *i, char **content, t_tok_lst **node)
{
	size_t	tmp;
	char	*s;

	tmp = *i;
	s = shell->input;
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
	return (EXIT_SUCCESS);
}

int	subshell_case(t_mini *shell, char *content, size_t *i)
{
	t_tok_lst	*node;
	char		*s;

	s = shell->input;
	node = NULL;
	content = NULL;
	if (subshell_utils(shell, i, &content, &node) == EXIT_FAILURE)
		return (EXIT_FAILURE);
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
