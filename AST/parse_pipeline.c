/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:56:16 by francema          #+#    #+#             */
/*   Updated: 2025/05/28 18:09:50 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*for cases like (cmd)) or (cmd)cmd)*/
bool	is_valid_operator(t_list **tokens)
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

t_ast_node	*parse_pipeline(t_mini *shell, t_list **tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*node;

	left = parse_simple_cmd(shell, tokens);
	if (is_valid_token(tokens) && !ft_strcmp((char *)(*tokens)->content, ")"))
	{
		if (!is_valid_operator(tokens) && shell->err_print == false)
		{
			shell->err_print = true;
			print_unexpected_token(tokens);
			free_ast(left);
			return (NULL); // syntax error after pipe
		}
		*tokens = (*tokens)->next; // consume ")"
		return (left);// return left if next token is ")" and next there is a valid operator
	}
	if (!left)
		return (NULL);
	while (is_valid_token(tokens) && !ft_strcmp((*tokens)->content, "|"))
	{
		*tokens = (*tokens)->next;// consume "|"
		right = parse_simple_cmd(shell, tokens);
		if (!right && is_valid_token(tokens))
			right = parse_subshell(shell, tokens);
		if (!right && shell->err_print == false)
		{
			shell->err_print = true;
			print_unexpected_token(tokens);
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
