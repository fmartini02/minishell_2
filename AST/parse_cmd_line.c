/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:57:00 by francema          #+#    #+#             */
/*   Updated: 2025/05/28 16:56:32 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_unexpected_token(t_list **tokens)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (!is_valid_token(tokens))
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd((char *)(*tokens)->content, 2);
	ft_putendl_fd("`", 2);
}

t_ast_node	*parse_cmd_line(t_mini *shell, t_list **tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*node;
	t_node_type	type;

	left = parse_pipeline(shell, tokens);
	if (!left)
		return (NULL);
	while (is_valid_token(tokens) && (!ft_strcmp((*tokens)->content, "&&")
			|| !ft_strcmp((*tokens)->content, "||")))
	{
		if (ft_strcmp((*tokens)->content, "&&") == 0)
			type = NODE_AND;
		else
			type = NODE_OR;
		*tokens = (*tokens)->next;
		if (shell->err_print == false)
			right = parse_pipeline(shell, tokens);
		if (!right && shell->err_print == false)
		{
			shell->err_print = true;
			print_unexpected_token(tokens);
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
	if (is_valid_token(tokens)
		&& !is_control_operator((*tokens)->content)
		&& ft_strcmp((*tokens)->content, ")") != 0
		&& shell->err_print == false)
	{
		shell->err_print = true;
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd((char *)(*tokens)->content, 2);
		ft_putendl_fd("`", 2);
		free_ast(left);
		return (NULL);
	}
	return (left);
}
