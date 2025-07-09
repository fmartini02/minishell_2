/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_doll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:32:09 by francema          #+#    #+#             */
/*   Updated: 2025/07/08 22:27:17 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	handle_ambiguous_redirect(t_mini *shell, size_t *i, char **res)
{
	char	*in;
	char	*tmp;

	in = shell->input;
	tmp = ft_dollar_case(shell, in, i);
	if (!tmp)
	{
		ft_putstr_fd("minishell: does variable exist?\n", 2);
		shell->err_print = true;
		free(*res);
		return;
	}
	size_t len = 0;
	while (tmp[len])
	{
		len = ft_skip_spaces(tmp, len);
		if (tmp[len] && tmp[len] != ' ')
		{
			while (tmp[len] && tmp[len] != ' ')
				len++;
			if (tmp[len] && tmp[len] == ' ' && tmp[len + 1] != ' ')
			{
				ft_putstr_fd("minishell: $: ambiguous redirect\n", 2);
				shell->err_print = true;
				free(tmp);
				free(*res);
				return;
			}
		}
	}
	*res = ft_strjoin_free(*res, tmp);
	free(tmp);
}

void	handle_dollar_expansion(t_mini *shell, size_t *i, char **res, size_t *start)
{
	char	*tmp;
	size_t	j;
	char	*in;

	in = shell->input;
	j = 0;
	if (should_print_doll_char(in, i) && in[*i + 1] != '\'' && in[*i + 1] != '"')
	{
		tmp = ft_strdup("$");
		if (!tmp)
			ft_fatal_memerr(shell);
		*res = ft_strjoin_free(*res, tmp);
		free(tmp);
		(*i)++;
		*start = *i;
		return;
	}
	if ((*i) > 0)
		j = *i - 1;
	while (j > 0 && !ft_ispecial_char(in[j]) && in[j] != ' ')
		j--;
	if (in[j] == '>' || in[j] == '<')
	{
		handle_ambiguous_redirect(shell, i, res);
		*start = *i;
		return;
	}
	*res = add_var(in, i, *res, shell);
	*start = *i;
}

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

void	handle_double_quotes(t_mini *shell, size_t *i, char **res, size_t *start)
{
	char	*tmp;
	char	*in;

	in = shell->input;
	tmp = NULL;
	(*i)++; // salta "
	while (in[*i] && in[*i] != '"')
	{
		if (in[*i] == '$')
		{
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
				*res = add_var(in, i, *res, shell);
			*start = *i;
		}
		if (in[*i] && in[*i] != '"')
			(*i)++;
	}
	if (in[*i] && in[*i] == '"')
		(*i)++;
	tmp = ft_substr(in, *start, *i - *start);
	if (!tmp)
		ft_fatal_memerr(shell);
	*res = ft_strjoin_free(*res, tmp);
	*start = *i;
	free(tmp);
}

void	handle_single_quotes(t_mini *shell, size_t *i, char **res, size_t *start)
{
	char	*tmp;
	char	*in;

	in = shell->input;
	tmp = NULL;
	(*i)++; // salta '
	while (in[*i] && in[*i] != '\'')
		(*i)++;
	(*i)++; // salta la chiusura '
	tmp = ft_substr(in, *start, *i - *start);
	if (!tmp)
		ft_fatal_memerr(shell);
	*res = ft_strjoin_free(*res, tmp);
	free(tmp);
	*start = *i;
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
			handle_single_quotes(shell, &i, &res, &start);
		else if (in[i] == '"')
			handle_double_quotes(shell, &i, &res, &start);
		else if (in[i] == '$')
			handle_dollar_expansion(shell, &i, &res, &start);
		else
			handle_plain_text(shell, &i, &res, &start);
	}
	shell->input = res;
}
