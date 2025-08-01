/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:56:16 by francema          #+#    #+#             */
/*   Updated: 2025/07/22 11:14:18 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*for cases like (cmd)) or (cmd)cmd)*/
bool	is_logic_operator(t_tok_lst **tokens)
{
	if (!is_valid_token(tokens))
		return (false);
	if (!(*tokens)->next)
		return (true);
	else if (!ft_strcmp((*tokens)->next->content, "&&")
		|| !ft_strcmp((*tokens)->next->content, "||")
		|| !ft_strcmp((*tokens)->next->content, "|"))
		return (true);
	return (false);
}

t_ast_node	*create_pipeline_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

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
	return (node);
}

// static t_ast_node	*check_closing_parenthesis(t_mini *shell,
// 	t_tok_lst **tokens, t_ast_node *left)
// {
// 	if (is_valid_token(tokens) && !ft_strcmp((char *)(*tokens)->content, ")"))
// 	{
// 		if (!is_logic_operator(tokens) && shell->err_print == false)
// 		{
// 			shell->err_print = true;
// 			print_unexpected_token(tokens);
// 			free_ast(left);
// 			return (NULL);
// 		}
// 		*tokens = (*tokens)->next;
// 		return (left);
// 	}
// 	return (NULL);
// }

t_ast_node	*operator_case(t_ast_node **left, t_mini *shell,
	t_tok_lst **tokens, t_ast_node *right)
{
	if (ft_strchr((*tokens)->content, '>')
		|| ft_strchr((*tokens)->content, '<'))
	{
		right = parse_simple_cmd(shell, tokens);
		if (!right && shell->err_print == false)
		{
			shell->err_print = true;
			print_unexpected_token(tokens);
			free_ast(*left);
			cleanup_shell(shell, -1);
			return (NULL);
		}
	}
	else
	{
		shell->err_print = true;
		print_unexpected_token(tokens);
		return (NULL);
	}
	return (right);
}

// if (is_valid_token(tokens) && !ft_strcmp((char *)(*tokens)->content, ")"))
// {
// 	left = check_closing_parenthesis(shell, tokens, left);
// 	if (!left)
// 		return (NULL);
// }
t_ast_node	*parse_pipeline(t_mini *shell, t_tok_lst **tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;

	left = parse_simple_cmd(shell, tokens);
	right = NULL;
	if (!left)
		return (NULL);
	if (!(*tokens)->next && !is_operator(tokens))
		return (left);
	left = pipeline_loop(&left, &right, shell, tokens);
	return (left);
}
