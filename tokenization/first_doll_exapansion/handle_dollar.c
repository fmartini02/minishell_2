/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:11:41 by francema          #+#    #+#             */
/*   Updated: 2025/07/15 17:49:24 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	expand_literal_dollar(t_mini *shell, size_t *i, char **res)
{
	char	*tmp;
	char	*in;

	in = shell->input;
	if (should_print_doll_char(in, i)
		&& in[*i + 1] != '\'' && in[*i + 1] != '"')
	{
		tmp = ft_strdup("$");
		if (!tmp)
			ft_fatal_memerr(shell);
		*res = ft_strjoin_free(*res, tmp);
		free(tmp);
		(*i)++;
		return (true);
	}
	return (false);
}

// bool	should_exand_doll(char *s, int i)
// {
// 	while(i > 0 && s[i] == ' ')
// 		i--;
// 	if (i > 0 && s[i] == '<' && i - 1 >= 0 && s[i - 1] == '<')
// 		return (true);
// }

void	handle_dollar_expansion(
	t_mini *shell, size_t *i, char **res, size_t *start)
{
	char	*in;
	size_t	j;

	in = shell->input;
	if (*i > 0)
		j = *i - 1;
	else
		j = 0;
	if (expand_literal_dollar(shell, i, res))
	{
		*start = *i;
		return ;
	}
	while (j > 0 && !ft_ispecial_char(in[j]) && in[j] != ' ')
		j--;
	if (in[j] == '>' || in[j] == '<')
	{
		handle_ambiguous_redirect(shell, i, res);
		*start = *i;
		return ;
	}
	*res = append_var(in, i, *res, shell);
	*start = *i;
}
