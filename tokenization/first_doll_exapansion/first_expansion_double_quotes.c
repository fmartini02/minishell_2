/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_expansion_double_quotes.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:13:15 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 16:10:47 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	handle_closing_double_quote(t_mini *shell, char *in, size_t *i)
{
	if (in[*i] != '"')
	{
		shell->err_print = true;
		ft_putendl_fd("minishell: unclosed \" quote", 2);
		return (false);
	}
	(*i)++;
	return (true);
}

bool	handle_dollar_inside_quotes(
	t_mini *shell, size_t *i, char **res, size_t *start)
{
	char	*tmp;
	char	*in;

	in = shell->input;
	tmp = ft_substr(in, *start, *i - *start);
	if (!tmp)
		ft_fatal_memerr(shell);
	*res = ft_strjoin_free(*res, tmp);
	free(tmp);
	if (should_print_doll_char(in, i))
	{
		tmp = ft_strdup("$");
		if (!tmp)
			ft_fatal_memerr(shell);
		*res = ft_strjoin_free(*res, tmp);
		free(tmp);
		(*i)++;
	}
	else
		*res = append_var(in, i, *res, shell);
	*start = *i;
	return (true);
}


