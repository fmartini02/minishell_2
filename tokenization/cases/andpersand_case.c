/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_case.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:44:09 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 18:44:16 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_tok_lst	*andpersand_case_utils(
	t_mini *shell, char *s, size_t *i)
{
	char		*content;
	t_tok_lst	*node;

	content = NULL;
	node = NULL;
	if (s[*i + 1] == '&')
	{
		content = ft_strdup("&&");
		node = new_tok_lst(content, AND, NULL);
		if (!content || !node)
		{
			if (content)
				free(content);
			ft_fatal_memerr(shell);
		}
		(*i) += 2;
	}
	else
	{
		content = NULL;
		node = NULL;
		(*i)++;
		return (NULL);
	}
	return (node);
}

int	andpersand_case(t_mini *shell, char *content, size_t *i)
{
	t_tok_lst	*node;
	char		*s;

	s = shell->input;
	node = andpersand_case_utils(shell, s, i);
	if (!node)
		return (EXIT_FAILURE);
	add_back_tok_lst(&(shell->tok_input), node);
	if (!shell->tok_input)
	{
		free(content);
		ft_fatal_memerr(shell);
	}
	return (EXIT_SUCCESS);
}
