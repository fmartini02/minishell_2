/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:57:00 by francema          #+#    #+#             */
/*   Updated: 2025/05/21 17:57:18 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast_node	*parse_cmd_line(t_mini *shell, t_list **tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*node;
	t_node_type	type;

	left = parse_pipeline(shell, tokens);
	if (!left)
		return (NULL);
	while (*tokens && (!ft_strcmp((*tokens)->content, "&&")
			|| !ft_strcmp((*tokens)->content, "||")))
	{
		if (ft_strcmp((*tokens)->content, "&&") == 0)
			type = NODE_AND;
		else
			type = NODE_OR;
		*tokens = (*tokens)->next;
		right = parse_pipeline(shell, tokens);
		if (!right)
		{
			if (type == NODE_AND)
				ft_putendl_fd("minishell: syntax error near unexpected token `&&`", 2);
			else
				ft_putendl_fd("minishell: syntax error near unexpected token `||`", 2);
			free_ast(left);
			return (NULL);
		}
		node = malloc(sizeof(t_ast_node));
		if (!node)
		{
			free_ast(left);
			free_ast(right);
			return (NULL);
		}
		node->type = type;
		node->left = left;
		node->right = right;
		node->content = NULL;
		node->next = NULL;
		left = node;
	}
	return (left);
}
