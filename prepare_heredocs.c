/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:11:11 by mdalloli          #+#    #+#             */
/*   Updated: 2025/06/26 14:24:22 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_heredoc_content(int write_fd, const char *delimiter)
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
		process_cmd_heredocs(cmd);
	}
}
