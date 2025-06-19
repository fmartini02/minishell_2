/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:44:03 by francema          #+#    #+#             */
/*   Updated: 2025/06/19 16:17:20 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*controlla se incontri un carattere delimitatore per le parole*/
static bool	is_word_delimiter(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&'
		|| c == '(' || c == ')' || c == '\'' || c == '"' || c == '$')
		return (true);
	return (false);
}

/*inizializza content basically*/
static bool	get_content(char **content, char *s, size_t *i, int *len)
{
	if (*len > 0)
	{
		content = ft_substr(s, *i, *len);
		if (!content)
			return (false);
		*i += *len;
		*len = 0;
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

	s = shell->input;
	len = 0;
	while (s[*i + len]
		&& !is_word_delimiter(s[*i + len])
		&& s[*i + len] != '\n'
		&& !ft_ispace(s[*i + len]))
		len++;
	if (!get_content(&content, s, i, &len))
		ft_fatal_memerr(shell);
	append_new_node(shell, content);
	return (EXIT_SUCCESS);
}
