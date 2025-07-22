/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:50:39 by francema          #+#    #+#             */
/*   Updated: 2025/07/22 10:46:45 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_ast_node	*parse_right_side_of_pipe(
	t_ast_node **left, t_mini *shell, t_tok_lst **tokens)
{
	t_ast_node	*right;

	right = NULL;
	if (is_valid_token(tokens) && is_operator(tokens))
		right = operator_case(left, shell, tokens, NULL);
	else if (!is_valid_token(tokens))
	{
		shell->err_print = true;
		print_unexpected_token(tokens);
		return (NULL);
	}
	if (!right && shell->err_print == false)
		right = parse_simple_cmd(shell, tokens);
	if (!right && shell->err_print == false)
	{
		shell->err_print = true;
		print_unexpected_token(tokens);
		free_ast(*left);
		cleanup_shell(shell, -1);
		return (NULL);
	}
	return (right);
}

static t_ast_node	*handle_pipeline_creation(
	t_ast_node **left, t_ast_node *right)
{
	t_ast_node	*node;

	node = create_pipeline_node(*left, right);
	if (!node)
		return (NULL);
	*left = node;
	return (node);
}

// if (!(*right) && is_valid_token(tokens))
// 	*right = parse_subshell(shell, tokens);
t_ast_node	*pipeline_loop(t_ast_node **left, t_ast_node **right,
	t_mini *shell, t_tok_lst **tokens)
{
	t_ast_node	*node;

	node = NULL;
	while (is_valid_token(tokens) && !ft_strcmp((*tokens)->content, "|"))
	{
		*tokens = (*tokens)->next;
		*right = parse_right_side_of_pipe(left, shell, tokens);
		if (!(*right) && shell->err_print == true)
			return (*left);
		node = handle_pipeline_creation(left, *right);
		if (!node)
			return (NULL);
		*right = NULL;
	}
	return (*left);
}
