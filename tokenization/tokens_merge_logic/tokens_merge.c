/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_merge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:18:02 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 16:17:33 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	append_double_wuote_token(t_mini *shell, char *content)
{
	t_tok_lst	*node;

	node = new_tok_lst(content, DOUBLE_QUOTES, NULL);
	if (!node)
		ft_fatal_memerr(shell);
	add_back_tok_lst(&(shell->tok_input), node);
	if (!shell->tok_input)
		ft_fatal_memerr(shell);
	return (EXIT_SUCCESS);
}

int	append_single_quote_token(t_mini *shell, char *content)
{
	t_tok_lst	*node;
	int			token_type;

	if (content[0] == '\0')
		token_type = DOUBLE_QUOTES;
	else
		token_type = SINGLE_QUOTES;
	node = new_tok_lst(content, token_type, NULL);
	if (!node)
		ft_fatal_memerr(shell);
	add_back_tok_lst(&(shell->tok_input), node);
	if (!shell->tok_input)
		ft_fatal_memerr(shell);
	return (EXIT_SUCCESS);
}

void	append_word_node(t_mini *shell, char *content)
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

char	*token_join(char *content, t_mini *shell, size_t *i)
{
	char	*tmp;

	tmp = to_join(shell->input, i, shell);
	if (!tmp)
	{
		free(content);
		if (shell->err_print)
			return (NULL);
		ft_fatal_memerr(shell);
	}
	content = ft_strjoin_free(content, tmp);
	if (!content)
	{
		free(tmp);
		ft_fatal_memerr(shell);
	}
	free(tmp);
	return (content);
}
