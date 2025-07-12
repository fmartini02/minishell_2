/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:38:41 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 15:48:26 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*redi_utils(t_mini *shell, char *s, size_t *i)
{
	char	*content;

	content = NULL;
	if (s[*i] == '<')
	{
		if (s[*i + 1] == '<')
			content = ft_strdup("<<");
		else
			content = ft_strdup("<");
	}
	else if (s[*i] == '>')
	{
		if (s[*i + 1] == '>')
			content = ft_strdup(">>");
		else
			content = ft_strdup(">");
	}
	if (!content)
		ft_fatal_memerr(shell);
	return (content);
}

int	redi_case(t_mini *shell, char *content, size_t *i)
{
	t_tok_lst	*node;
	char		*s;

	s = shell->input;
	content = redi_utils(shell, s, i);
	node = new_tok_lst(content, REDIRECT, NULL);
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
	*i += ft_strlen(content);
	return (EXIT_SUCCESS);
}
