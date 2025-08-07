/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_doll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:32:09 by francema          #+#    #+#             */
/*   Updated: 2025/08/07 16:26:35 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_plain_text(t_mini *shell, size_t *i, char **res, size_t *start)
{
	char	*tmp;
	char	*in;

	in = shell->input;
	while (in[*i] && in[*i] != '$' && in[*i] != '\'' && in[*i] != '"')
		(*i)++;
	tmp = ft_substr(in, *start, *i - *start);
	if (!tmp)
		ft_fatal_memerr(shell);
	*res = ft_strjoin_free(*res, tmp);
	free(tmp);
	*start = *i;
}

static void	handle_single(
	t_mini *shell, size_t *i, char **res, size_t *start)
{
	char	*tmp;
	char	*in;

	in = shell->input;
	tmp = NULL;
	(*i)++;
	while (in[*i] && in[*i] != '\'')
		(*i)++;
	if (in[*i] != '\'')
	{
		shell->err_print = true;
		ft_putendl_fd("minishell: unclosed \' quote", 2);
		return ;
	}
	(*i)++;
	tmp = ft_substr(in, *start, *i - *start);
	if (!tmp)
		ft_fatal_memerr(shell);
	*res = ft_strjoin_free(*res, tmp);
	free(tmp);
	*start = *i;
}

static void	handle_double(t_mini *shell, size_t *i, char **res, size_t *start)
{
	char	*in;
	char	*tmp;

	in = shell->input;
	tmp = NULL;
	(*i)++;
	while (in[*i] && in[*i] != '"')
	{
		if (in[*i] == '$')
		{
			if (!handle_dollar_inside_quotes(shell, i, res, start))
				return ;
		}
		if (in[*i] && in[*i] != '"')
			(*i)++;
	}
	if (!handle_closing_double_quote(shell, in, i))
		return ;
	tmp = ft_substr(in, *start, *i - *start);
	if (!tmp)
		ft_fatal_memerr(shell);
	*res = ft_strjoin_free(*res, tmp);
	*start = *i;
	free(tmp);
}

void	expand_doll(t_mini *shell, char *in)
{
	char	*res;
	size_t	i;
	size_t	start;

	res = NULL;
	i = 0;
	start = 0;
	while (in[i])
	{
		if (in[i] == '\'')
			handle_single(shell, &i, &res, &start);
		else if (in[i] == '"')
			handle_double(shell, &i, &res, &start);
		else if (in[i] == '$')
			handle_dollar_expansion(shell, &i, &res, &start);
		else
			handle_plain_text(shell, &i, &res, &start);
	}
	free(shell->input);
	shell->input = res;
}
