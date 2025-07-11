/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:28:38 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/11 23:29:27 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_input_redirection(t_redirection *redir, t_mini *shell, int *last_in)
{
	int	fd;

	fd = open_redir_fd(redir);
	if (fd < 0)
	{
		if (!shell->err_print)
			perror(redir->target);
		shell->err_print = true;
		return (-1);
	}
	if (*last_in != -1 && *last_in != STDIN_FILENO)
		close(*last_in);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	*last_in = fd;
	return (0);
}

int	handle_output_redirection(t_redirection *redir, t_mini *shell)
{
	int	fd;

	fd = open_redir_fd(redir);
	if (fd < 0)
	{
		perror(redir->target);
		shell->err_print = true;
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

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

int	handle_heredoc(t_redirection *redir)
{
	if (redir->heredoc_fd != -1)
	{
		if (dup2(redir->heredoc_fd, STDIN_FILENO) == -1)
			return (perror("dup2 heredoc"), -1);
		close(redir->heredoc_fd);
		redir->heredoc_fd = -1;
	}
	return (0);
}
