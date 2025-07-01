/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:11:11 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/01 19:05:57 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// minishell.h

extern volatile sig_atomic_t	g_sig_code;

/* static void	fill_heredoc_content(int write_fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

static void	setup_heredoc_pipe(t_redirection *redir)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		exit(1);
	fill_heredoc_content(pipefd[1], redir->target);
	close(pipefd[1]);
	redir->heredoc_fd = pipefd[0];
}

static void	process_cmd_heredocs(t_cmd_info *cmd)
{
	t_redirection	*redir;

	if (!cmd)
		return ;
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			setup_heredoc_pipe(redir);
		redir = redir->next;
	}
}

void	prepare_heredocs(t_ast_node *ast)
{
	t_cmd_info	*cmd;

	if (!ast)
		return ;
	if (ast->type == NODE_PIPELINE)
	{
		prepare_heredocs(ast->left);
		prepare_heredocs(ast->right);
	}
	else if (ast->type == NODE_CMD)
	{
		cmd = (t_cmd_info *)ast->content;
		if (cmd)
			process_cmd_heredocs(cmd);
	}
} */

static int	heredoc_read_loop(int write_fd, const char *delimiter,
	struct sigaction *old_sa)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_sig_code == 130)
		{
			free(line);
			return (sigaction_return(old_sa, -1));
		}
		if (!line)
		{
			write_ctrld(delimiter);
			return (sigaction_return(old_sa, -1));
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	return (sigaction_return(old_sa, 0));
}

static int	fill_heredoc_content(int write_fd, const char *delimiter)
{
	struct sigaction	sa;
	struct sigaction	old_sa;

	g_sig_code = 0;
	sa.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, &old_sa);
	return (heredoc_read_loop(write_fd, delimiter, &old_sa));
}

static int	setup_heredoc_pipe(t_redirection *redir)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	if (fill_heredoc_content(pipefd[1], redir->target) < 0)
	{
		close(pipefd[1]);
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[1]);
	redir->heredoc_fd = pipefd[0];
	return (0);
}

static int	process_cmd_heredocs(t_cmd_info *cmd)
{
	t_redirection	*redir;

	if (!cmd)
		return (0);
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			if (setup_heredoc_pipe(redir) < 0)
				return (-1);
		redir = redir->next;
	}
	return (0);
}

int	prepare_heredocs(t_ast_node *ast)
{
	t_cmd_info	*cmd;
	int			ret;

	ret = 0;
	if (!ast)
		return (0);
	if (ast->type == NODE_PIPELINE)
	{
		if (prepare_heredocs(ast->left) < 0)
			return (-1);
		if (prepare_heredocs(ast->right) < 0)
			return (-1);
	}
	else if (ast->type == NODE_CMD)
	{
		cmd = (t_cmd_info *)ast->content;
		if (cmd)
			ret = process_cmd_heredocs(cmd);
	}
	return (ret);
}
