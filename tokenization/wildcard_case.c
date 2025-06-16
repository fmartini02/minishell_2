/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:58:42 by francema          #+#    #+#             */
/*   Updated: 2025/06/11 17:07:38 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wildcard_case(t_mini *shell, char *content, size_t *i)
{
	char		*s;
	t_tok_lst	*node;

	s = shell->input;
	while (s[*i] && s[*i] == '*')
		(*i)++;
	content = ft_strdup("*");
	node = new_tok_lst(content, WILDCARD, NULL);
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
	return (EXIT_SUCCESS);
}
