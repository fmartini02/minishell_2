/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:09:53 by francema          #+#    #+#             */
/*   Updated: 2025/07/15 15:18:25 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	is_ambiguous(char *value)
{
	size_t	i;

	i = 0;
	while (value[i])
	{
		i = ft_skip_spaces(value, i);
		if (value[i] && value[i] != ' ')
		{
			while (value[i] && value[i] != ' ')
				i++;
			if (value[i] && value[i] == ' ' && value[i + 1] != ' ')
				return (true);
		}
	}
	return (false);
}

void	handle_ambiguous_redirect(t_mini *shell, size_t *i, char **res)
{
	char	*tmp;

	tmp = ft_dollar_case(shell, shell->input, i);
	if (!tmp)
	{
		ft_putstr_fd("minishell: does variable exist?\n", 2);
		shell->err_print = true;
		free(*res);
		return ;
	}
	if (is_ambiguous(tmp))
	{
		ft_putstr_fd("minishell: $: ambiguous redirect\n", 2);
		shell->err_print = true;
		free(tmp);
		free(*res);
		*res = NULL;
		return ;
	}
	*res = ft_strjoin_free(*res, tmp);
	free(tmp);
}
