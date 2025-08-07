/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:06:49 by francema          #+#    #+#             */
/*   Updated: 2025/08/07 16:43:24 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_ast(t_ast_node *node, t_mini *shell)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD)
		handle_node_cmd(node, shell);
	else if (node->type == NODE_PIPELINE)
		execute_pipeline(node, shell);
}
	// else
	// 	execute_logic(node, shell);
