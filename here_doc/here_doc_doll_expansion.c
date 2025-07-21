/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_doll_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:51:22 by francema          #+#    #+#             */
/*   Updated: 2025/07/19 16:03:42 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*heredoc_append_var(
	char *line, size_t *i, char *to_print, t_mini *shell)
{
	char	*tmp;

	if (should_print_doll_char(line, i))
	{
		to_print = ft_strjoin_free(to_print, "$");
		if (!to_print)
			ft_fatal_memerr(shell);
		(*i)++;
		return (to_print);
	}
	tmp = ft_dollar_case(shell, line, i);
	if (!tmp)
		ft_fatal_memerr(shell);
	to_print = ft_strjoin_free(to_print, tmp);
	if (!to_print)
		ft_fatal_memerr(shell);
	free(tmp);
	return (to_print);
}

void	append_substr(
	char **to_print, char *line, size_t start, size_t end)
{
	char	*tmp;

	tmp = ft_substr(line, start, end - start);
	if (!tmp)
	{
		*to_print = NULL;
		return ;
	}
	*to_print = ft_strjoin_free(*to_print, tmp);
	if (tmp)
		free(tmp);
}

static void	input_handling(
	char *line, size_t *i, char **to_print, t_mini *shell)
{
	size_t	start;

	start = *i;
	while (line[*i])
	{
		if (line[*i] == '$')
		{
			if (*i > start)
			{
				append_substr(to_print, line, start, *i);
				if (!*to_print)
					ft_fatal_memerr(shell);
			}
			*to_print = heredoc_append_var(line, i, *to_print, shell);
			start = *i;
		}
		else
			(*i)++;
	}
	if (*i > start)
		append_substr(to_print, line, start, *i);
	if (!*to_print)
		ft_fatal_memerr(shell);
}

void	apply_doll_exansion(int write_fd, char *line, t_mini *shell)
{
	size_t	i;
	char	*to_print;

	i = ft_skip_spaces(line, 0);
	to_print = NULL;
	while (line[i])
		input_handling(line, &i, &to_print, shell);
	write(write_fd, to_print, ft_strlen(to_print));
	write(write_fd, "\n", 1);
	free(line);
	free(to_print);
}
