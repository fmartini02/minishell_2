/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:36:22 by francema          #+#    #+#             */
/*   Updated: 2025/07/10 19:12:52 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_eof(char *s, size_t i)
{
	i--;
	if (i > 0 && s[i] == ' ')
	{
		while (i > 0 && s[i] == ' ')
			i--;
	}
	if (s[i] != ' ' && s[i] == '<')
	{
		if (i - 1 > 0 && s[i - 1] == '<')
			return (true);
	}
	return (false);
}

static char	*single_quotes_utils(t_mini *shell, char *s, size_t *i,
	char *content)
{
	size_t		start;
	char		*tmp;
	bool		eof;

	start = 0;
	if (s[*i] == '\'' && s[*i + 1] == '\'')
		return((*i) += 2, ft_strdup(""));
	if (s[*i] == '"' && s[*i +1] ==' ')
	{
		start = ft_skip_spaces(s, *i + 1);
		if (s[start] == '"')
			return (*i = start + 2, ft_strdup(""));
	}
	if ((s[*i] == '\'' && !s[*i + 1]))
		return ((*i)++, NULL);
	eof = is_eof(s, *i);
	start = ++(*i);
	tmp = NULL;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (s[*i] != '\'')
	{
		ft_putstr_fd("minishell: unclosed single quote\n", 2);
		return (NULL);
	}
	if (eof)
		tmp = ft_substr(s, start - 1, (*i + 2) - start);
	else
		tmp = ft_substr(s, start, *i - start);
	if (!tmp)
		ft_fatal_memerr(shell);
	content = ft_strjoin_free(content, tmp);
	free(tmp);
	if (!content)
		ft_fatal_memerr(shell);
	(*i)++;
	return (content);
}

int	single_quotes_case(t_mini *shell, char *content, size_t *i)
{
	char		*s;
	//char		*tmp;
	t_tok_lst	*node;

	s = shell->input;
	//tmp = NULL;
	content = single_quotes_utils(shell, s, i, content);
	if (!content)
		return (EXIT_FAILURE);
	if (s[*i] && s[*i] != '<' && s[*i] != '>' && s[*i] != '|' && s[*i] != ' ')
		content = token_join(content, shell, i);
	if (content[0] == '\0')
	{
		node = new_tok_lst(content, DOUBLE_QUOTES, NULL);
		if (!node)
			ft_fatal_memerr(shell);
		add_back_tok_lst(&(shell->tok_input), node);
		if (!shell->tok_input)
			ft_fatal_memerr(shell);
		return (EXIT_SUCCESS);
	}
	node = new_tok_lst(content, SINGLE_QUOTES, NULL);
	if (!node)
		ft_fatal_memerr(shell);
	add_back_tok_lst(&(shell->tok_input), node);
	if (!shell->tok_input)
		ft_fatal_memerr(shell);
	return (EXIT_SUCCESS);
}
