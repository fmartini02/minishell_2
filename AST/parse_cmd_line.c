/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:57:00 by francema          #+#    #+#             */
/*   Updated: 2025/06/30 18:27:48 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_unexpected_token(t_tok_lst *tokens)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (!is_valid_token(tokens))
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(tokens->content, 2);
	ft_putendl_fd("`", 2);
}

t_node_type	get_node_type(t_tok_lst *token)
{
	if (!ft_strcmp(token->content, "&&"))
		return (NODE_AND);
	if (!ft_strcmp(token->content, "||"))
		return (NODE_OR);
	if (!ft_strcmp(token->content, "("))
		return (NODE_SUBSHELL);
	return (NODE_PIPELINE);
}

t_ast_node	*create_ast_node(t_node_type type, t_ast_node *left,
	t_ast_node *right)
{
	t_ast_node	*node;

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
	return (node);
}

bool	handle_cmdline_error(t_mini *shell, t_tok_lst *tokens,
	t_ast_node *left)
{
	if (is_valid_token(tokens)
		&& !is_control_operator(tokens->content)
		&& !ft_strcmp(tokens->content, ")")
		&& shell->err_print == false)
	{
		shell->err_print = true;
		print_unexpected_token(tokens);
		free_ast(left);
		return (true);
	}
	return (false);
}

// type = get_node_type(*tokens);
// if (type == NODE_SUBSHELL)
// 	right = parse_subshell(shell, tokens);
// if (!right && type == NODE_SUBSHELL)
// 	return (NULL);
t_ast_node	*cmd_line_loop(t_mini *shell, t_tok_lst *tokens, t_ast_node *left)
{
	t_ast_node	*right;
	t_node_type	type;

	right = NULL;
	type = NODE_PIPELINE;
	while (is_valid_token(tokens) && is_control_operator(tokens->content))
	{
		tokens = tokens->next;
		if (shell->err_print == false)
			right = parse_pipeline(shell, tokens);
		if (!right && shell->err_print == false)
		{
			shell->err_print = true;
			return (print_unexpected_token(tokens), free_ast(left), NULL);
		}
		left = create_ast_node(type, left, right);
		if (!left)
			return (NULL);
	}
	return (left);
}

t_ast_node	*parse_cmd_line(t_mini *shell, t_tok_lst *tokens)
{
	t_ast_node	*left;

	left = parse_pipeline(shell, tokens);
	if (!left)
		return (NULL);
	if (is_valid_token(tokens) && !ft_strcmp(tokens->content, ")"))
		return (left);
	left = cmd_line_loop(shell, tokens, left);
	if (handle_cmdline_error(shell, tokens, left))
		return (NULL);
	return (left);
}
