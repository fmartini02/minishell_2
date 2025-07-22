/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:07:13 by francema          #+#    #+#             */
/*   Updated: 2025/07/22 10:55:13 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_text(t_tok_lst **tokens)
{
	if (!is_valid_token(tokens))
		return (0);
	if ((*tokens)->type == DOUBLE_QUOTES
		|| (*tokens)->type == SINGLE_QUOTES
		|| (*tokens)->type == WORD)
		return (1);
	return (0);
}

int	is_operator(t_tok_lst **token)
{
	if (!(*token)->content)
		return (0);
	if (is_text(token))
		return (0);
	return (!ft_strcmp((*token)->content, "|")
		|| !ft_strcmp((*token)->content, "<")
		|| !ft_strcmp((*token)->content, ">")
		|| !ft_strcmp((*token)->content, "<<")
		|| !ft_strcmp((*token)->content, ">>"));
}


bool	is_valid_token(t_tok_lst **tokens)
{
	return (tokens && *tokens && (*tokens)->content);
}
