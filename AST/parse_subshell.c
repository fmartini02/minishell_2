/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:54:07 by francema          #+#    #+#             */
/*   Updated: 2025/05/26 19:11:22 by francema         ###   ########.fr       */
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
	//printf("%s\n", (char *)(*tokens)->content);
	subtree = parse_cmd_line(shell, tokens);
	if (!subtree)
		return (NULL);
	if ((!is_valid_token(tokens)
		|| ft_strcmp((char *)(*tokens)->content, ")")))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (!is_valid_token(tokens))
			ft_putstr_fd("newline", 2);
		else
			ft_putendl_fd((char *)(*tokens)->content, 2);
		ft_putendl_fd("`", 2);
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
