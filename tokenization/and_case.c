/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_case.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:34:06 by francema          #+#    #+#             */
/*   Updated: 2025/06/11 17:12:06 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	and_case(t_mini *shell, char *content, size_t *i)
{
	t_tok_lst	*node;
	char		*s;

	s = shell->input;
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
		return (EXIT_FAILURE);
	}
	add_back_tok_lst(&(shell->tok_input), node);
	if (!shell->tok_input)
	{
		free(content);
		ft_fatal_memerr(shell);
	}
	return (EXIT_SUCCESS);
}
