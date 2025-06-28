/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:28:38 by mdalloli          #+#    #+#             */
/*   Updated: 2025/06/28 16:00:00 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir_fd(t_redirection *redir)
{
	if (redir->type == REDIR_INPUT)
		return (open(redir->target, O_RDONLY));
	else if (redir->type == REDIR_OUTPUT)
		return (open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (redir->type == REDIR_APPEND)
		return (open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

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
