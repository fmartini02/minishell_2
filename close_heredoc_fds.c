/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_heredoc_fds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:36:00 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/01 13:47:37 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_heredoc_fds_cmd(t_cmd_info *cmd)
{
	t_redirection	*redir;

	redir = NULL;
	if (cmd)
		redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC && redir->heredoc_fd != -1)
		{
			close(redir->heredoc_fd);
			redir->heredoc_fd = -1;
		}
		redir = redir->next;
	}
}

void	close_all_heredoc_fds(t_ast_node *ast)
{
	t_cmd_info	*cmd;

	if (!ast)
		return ;
	if (ast->type == NODE_PIPELINE)
	{
		close_all_heredoc_fds(ast->left);
		close_all_heredoc_fds(ast->right);
	}
	else if (ast->type == NODE_CMD)
	{
		cmd = (t_cmd_info *)ast->content;
		if (cmd)
			close_heredoc_fds_cmd(cmd);
	}
}
