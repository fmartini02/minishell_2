/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:37:24 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 18:45:38 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_pipe_err(t_mini *shell)
{
	shell->err_print = true;
	ft_putendl_fd("syntax error empty pipeline", 2);
}

int	pipe_char_case(t_mini *shell, char *content, size_t *i)
{
	t_tok_lst	*node;
	char		*s;

	s = shell->input;
	if (s[*i + 1] == '|')
		return (print_pipe_err(shell), EXIT_FAILURE);
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
