/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:07:13 by francema          #+#    #+#             */
/*   Updated: 2025/05/22 17:36:11 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_control_operator(char *token)
{
	if (!token)
		return (0);
	return (!ft_strcmp(token, "|")
		|| !ft_strcmp(token, "&&")
		|| !ft_strcmp(token, "||")
		|| !ft_strcmp(token, "(")
		|| !ft_strcmp(token, ")")
		|| !ft_strcmp(token, "<")
		|| !ft_strcmp(token, ">")
		|| !ft_strcmp(token, "<<")
		|| !ft_strcmp(token, ">>"));
}

// Frees redirections linked list
void	free_redirections(t_redirection *redir)
{
	t_redirection	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->target);
		free(redir);
		redir = tmp;
	}
}

void	free_cmd_info(t_cmd_info *cmd)
{
	int i = 0;
	if (!cmd)
		return;
	if (cmd->cmd_name)
		free(cmd->cmd_name);
	if (cmd->cmd_args)
	{
		while (cmd->cmd_args[i])
			free(cmd->cmd_args[i++]);
		free(cmd->cmd_args);
	}
	free_redirections(cmd->redirections);
	free(cmd);
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;

	if (node->type == NODE_CMD && node->content)
		free_cmd_info((t_cmd_info *)node->content);
	else if (node->type == NODE_SUBSHELL && node->content)
		free_ast((t_ast_node *)node->content);

	// Recursively free left and right subtrees
	free_ast(node->left);
	free_ast(node->right);

	// Nullify and free the current node
	node->left = NULL;
	node->right = NULL;
	node->content = NULL;
	free(node);
}
