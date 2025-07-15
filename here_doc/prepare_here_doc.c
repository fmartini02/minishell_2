/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:58:03 by francema          #+#    #+#             */
/*   Updated: 2025/07/15 18:40:10 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	fill_heredoc_pipe(int pip_fd, char *eof, t_mini *shell)
{
	struct sigaction	old_sa;

	setup_heredoc_signals(&old_sa);
	return (heredoc_read_loop(pip_fd, eof, &old_sa, shell));
}

static int	setup_heredoc_pipe(t_redirection *redir, t_mini *shell)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		cleanup_shell(shell, -1);
		return (-1);
	}
	if (fill_heredoc_pipe(pipefd[1], redir->target, shell) < 0)
	{
		close(pipefd[1]);
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[1]);
	redir->heredoc_fd = pipefd[0];
	return (0);
}

static int	get_here_doc_inputs(t_cmd_info *cmd, t_mini *shell)
{
	t_redirection	*redir;

	if (!cmd)
		return (0);
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			if (setup_heredoc_pipe(redir, shell) < 0)
				return (-1);
		redir = redir->next;
	}
	return (0);
}

int	prepare_heredocs(t_ast_node *ast, t_mini *shell)
{
	t_cmd_info	*cmd;
	int			ret;

	ret = 0;
	if (!ast)
		return (0);
	if (ast->type == NODE_PIPELINE)
	{
		if (prepare_heredocs(ast->left, shell) < 0)
			return (-1);
		if (prepare_heredocs(ast->right, shell) < 0)
			return (-1);
	}
	else if (ast->type == NODE_CMD)
	{
		cmd = (t_cmd_info *)ast->content;
		if (cmd)
			ret = get_here_doc_inputs(cmd, shell);
	}
	return (ret);
}

void	handle_eventual_heredoc(t_ast_node *node, t_mini *shell)
{
	if (prepare_heredocs(node, shell) < 0)
	{
		close_all_heredoc_fds(node);
		return ;
	}
	if (g_sig_code == true)
	{
		g_sig_code = 0;
		return ;
	}
}
