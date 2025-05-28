/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:56:16 by francema          #+#    #+#             */
/*   Updated: 2025/05/27 17:43:36 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast_node	*parse_pipeline(t_mini *shell, t_list **tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*node;

	left = parse_simple_cmd(shell, tokens);
	if ((is_valid_token(tokens)
		&& ((!ft_strcmp((char *)(*tokens)->content, "("))
		|| !ft_strcmp((char *)(*tokens)->content, ")"))))
		left = parse_subshell(shell, tokens);
	if (!left)
		return (NULL);
	while (is_valid_token(tokens) && !ft_strcmp((*tokens)->content, "|"))
	{
		*tokens = (*tokens)->next;// consume "|"
		right = parse_simple_cmd(shell, tokens);
		if (!right && is_valid_token(tokens))
			right = parse_subshell(shell, tokens);
		if (!right)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			if (!is_valid_token(tokens))
				ft_putstr_fd("newline", 2);
			else
				ft_putstr_fd((char *)(*tokens)->content, 2);
			ft_putendl_fd("`", 2);
			free_ast(left);
			return (NULL); // syntax error after pipe
		}
		node = malloc(sizeof(t_ast_node));
		if (!node)
		{
			free_ast(left);
			free_ast(right);
			return (NULL);
		}
		node->type = NODE_PIPELINE;
		node->left = left;
		node->right = right;
		node->next = NULL;
		node->content = NULL;
		left = node; // chain left side
	}
	return (left);
}
