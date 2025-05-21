/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:54:07 by francema          #+#    #+#             */
/*   Updated: 2025/05/21 17:54:26 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast_node	*parse_subshell(t_mini *shell, t_list **tokens)
{
	t_ast_node	*subtree;
	t_ast_node	*node;

	if (!tokens || !*tokens || !(*tokens)->next)
		return (NULL);
	*tokens = (*tokens)->next;
	subtree = parse_cmd_line(shell, tokens);
	if (!subtree || !(*tokens)->content
		|| ft_strcmp((char *)(*tokens)->content, ")") != 0)
	{
		if (!*tokens || !(*tokens)->content)
			ft_putendl_fd("minishell: syntax error near unexpected token `newline`", 2);
		else
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `", 2);
			ft_putendl_fd((char *)(*tokens)->content, 2);
			ft_putendl_fd("`", 2);
		}
		free_ast(subtree);
		return (NULL);
	}
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
