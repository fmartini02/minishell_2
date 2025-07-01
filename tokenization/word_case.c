/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:44:03 by francema          #+#    #+#             */
/*   Updated: 2025/06/30 20:25:26 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	append_new_node(t_mini *shell, char *content)
{
	t_tok_lst	*node;

	node = new_tok_lst(content, WORD, NULL);
	if (!node || !content)
	{
		if (content)
			free(content);
		ft_fatal_memerr(shell);
	}
	add_back_tok_lst(&(shell->tok_input), node);
	if (!shell->tok_input)
	{
		free(content);
		ft_fatal_memerr(shell);
	}
}

int	word_case(t_mini *shell, char *content, size_t *i)
{
	char		*s;
	int			len;
	int			end;

	s = shell->input;
	len = 0;
	while (s[*i + len]
		&& !is_word_delimiter(s[*i + len])
		&& s[*i + len] != '\n'
		&& !ft_ispace(s[*i + len]))
		len++;
	end = len + *i;
	if (!get_content(&content, s, i, end))
		ft_fatal_memerr(shell);
	append_new_node(shell, content);
	return (EXIT_SUCCESS);
}
