/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:54:07 by francema          #+#    #+#             */
/*   Updated: 2025/05/28 16:57:32 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast_node	*parse_subshell(t_mini *shell, t_list **tokens)
{
	t_ast_node	*subtree;
	t_ast_node	*node;

	if (!is_valid_token(tokens))
		return (NULL);
	if (!(*tokens)->next && shell->err_print == false)
	{
		shell->err_print = true;
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putendl_fd("newline`", 2);
		*tokens = (*tokens)->next;
		return (NULL);
	}
	*tokens = (*tokens)->next; // skip the opening parenthesis
	subtree = parse_cmd_line(shell, tokens);
	if (!subtree)
		return (NULL);
	if ((!is_valid_token(tokens)
		|| ft_strcmp((char *)(*tokens)->content, ")")) && shell->err_print == false)
	{
		shell->err_print = true;
		print_unexpected_token(tokens);
		free_ast(subtree);
		return (NULL);
	}
	if (is_valid_token(tokens))
		*tokens = (*tokens)->next;
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
