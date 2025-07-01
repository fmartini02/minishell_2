/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:54:07 by francema          #+#    #+#             */
/*   Updated: 2025/07/01 12:09:59 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast_node	*create_subshell_node(t_ast_node *subtree)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
	{
		free_ast(subtree);
		return (NULL);
	}
	node->type = NODE_SUBSHELL;
	node->content = subtree;
	node->left = NULL;
	node->right = NULL;
	node->next = NULL;
	return (node);
}

bool	handle_opening_paren(t_mini *shell, t_tok_lst **tokens)
{
	if (!is_valid_token(tokens))
		return (false);
	if (!(*tokens)->next && shell->err_print == false)
	{
		shell->err_print = true;
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putendl_fd("newline`", 2);
		(*tokens) = (*tokens)->next;
		return (false);
	}
	(*tokens) = (*tokens)->next;
	return (true);
}

bool	handle_closing_paren(t_mini *shell, t_tok_lst **tokens)
{
	if (!is_valid_token(tokens)
		|| ft_strcmp((*tokens)->content, ")"))
	{
		if (shell->err_print == false)
		{
			shell->err_print = true;
			print_unexpected_token(tokens);
		}
		return (false);
	}
	(*tokens) = (*tokens)->next;
	return (true);
}

t_ast_node	*parse_subshell(t_mini *shell, t_tok_lst **tokens)
{
	t_ast_node	*subtree;

	if (!handle_opening_paren(shell, tokens))
		return (NULL);
	subtree = parse_cmd_line(shell, tokens);
	if (!subtree)
		return (NULL);
	if (!handle_closing_paren(shell, tokens))
	{
		free_ast(subtree);
		return (NULL);
	}
	return (create_subshell_node(subtree));
}
