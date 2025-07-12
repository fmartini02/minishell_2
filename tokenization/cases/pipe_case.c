/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:37:24 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 15:48:15 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pipe_char_case(t_mini *shell, char *content, size_t *i)
{
	t_tok_lst	*node;
	char		*s;

	s = shell->input;
	if (s[*i + 1] == '|')
		content = ft_strdup("||");
	else
		content = ft_strdup("|");
	node = new_tok_lst(content, PIPE, NULL);
	if (!content || !node)
	{
		if (content)
			free(content);
		ft_fatal_memerr(shell);
	}
	*i += ft_strlen(content);
	add_back_tok_lst(&(shell->tok_input), node);
	if (!shell->tok_input)
	{
		free(content);
		ft_fatal_memerr(shell);
	}
	return (EXIT_SUCCESS);
}
