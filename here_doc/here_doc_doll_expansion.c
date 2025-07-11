/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_doll_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:51:22 by francema          #+#    #+#             */
/*   Updated: 2025/07/11 22:45:42 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_var(char *line, size_t *i, char *to_print, t_mini *shell)
{
	char	*tmp;

	tmp = ft_dollar_case(shell, line, i);
	if (!tmp)
		ft_fatal_memerr(shell);
	to_print = ft_strjoin_free(to_print, tmp);
	free(tmp);
	return (to_print);
}

static void	handle_single_quotes(char *line, size_t *i,
	char **to_print, t_mini *shell)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != '\'')
	{
		if (line[*i] == '$')
		{
			append_substr(to_print, line, start, *i);
			if (!*to_print)
				ft_fatal_memerr(shell);
			*to_print = append_var(line, i, *to_print, shell);
			start = *i;
		}
		(*i)++;
	}
}

static void	handle_double_quotes(char *line, size_t *i,
	char **to_print, t_mini *shell)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		if (line[*i] == '$')
		{
			append_substr(to_print, line, start, *i);
			if (!*to_print)
				ft_fatal_memerr(shell);
			*to_print = append_var(line, i, *to_print, shell);
			start = *i;
		}
		(*i)++;
	}
}

static void	quotes_handling(char *line, size_t *i,
	char **to_print, t_mini *shell)
{
	while (line[*i] && line[*i] != ' ' && line[*i] != '$')
	{
		if (line[*i] == '\'')
			handle_single_quotes(line, i, to_print, shell);
		else if (line[*i] == '"')
			handle_double_quotes(line, i, to_print, shell);
		(*i)++;
	}
}

void	apply_doll_exansion(int write_fd, char *line, t_mini *shell)
{
	size_t	i;
	size_t	start;
	char	*to_print;

	i = 0;
	start = 0;
	to_print = NULL;
	while (line[i])
	{
		quotes_handling(line, &i, &to_print, shell);
		if (line[i] != '$')
		{
			append_substr(&to_print, line, start, i);
			if (!*to_print)
				ft_fatal_memerr(shell);
		}
		start = i;
		if (line[i] == '$')
			to_print = append_var(line, &i, to_print, shell);
	}
	write(write_fd, to_print, ft_strlen(to_print));
	write(write_fd, "\n", 1);
	free(line);
	free(to_print);
}
