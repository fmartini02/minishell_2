/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:44:03 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 15:55:29 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*inizializza content basically*/
static bool	get_content(char **content, char *s, size_t *i, int len)
{
	if (len > 0)
	{
		*content = ft_substr(s, *i, len - *i);
		if (!content)
			return (false);
		*i = len;
	}
	return (true);
}

int	word_case(t_mini *shell, char *content, size_t *i)
{
	char		*s;
	int			len;
	int			end;

	s = shell->input;
	len = 0;
	while (s[*i + len]
		&& (!is_word_delimiter(s[*i + len]))
		&& s[*i + len] != '\n'
		&& !ft_ispace(s[*i + len]))
		len++;
	if (s[*i + len] && s[*i + len] != '<'
		&& s[*i + len] != '>' && s[*i + len] != '|'
		&& s[*i + len] != ' ')
		content = token_join(content, shell, i);
	else
	{
		end = len + *i;
		if (!get_content(&content, s, i, end))
			ft_fatal_memerr(shell);
	}
	append_word_node(shell, content);
	return (EXIT_SUCCESS);
}
