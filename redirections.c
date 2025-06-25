/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:23:20 by mdalloli          #+#    #+#             */
/*   Updated: 2025/06/25 12:23:22 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// here_doc gestito nella pipeline
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
/*
int	apply_redirections(t_mini *shell)
{
	t_redirection	*redir;
	int				fd;

	redir = shell->cmd_info->redirections;
	while (redir)
	{
		fd = open_redir_fd(redir);
		if (fd < 0)
		{
			if (!shell->err_print)
				perror(redir->target);
			shell->err_print = true;
			return (-1);
		}
		if (redir->type == REDIR_INPUT)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
	return (0);
} */

int	apply_redirections(t_exec_unit *unit, t_mini *shell)
{
	t_redirection	*redir = unit->redirs;
	int				fd;
	int				pipe_fds[2];
	char			*line;

	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			if (pipe(pipe_fds) == -1)
				return (perror("pipe"), -1);
			while (1)
			{
				line = readline("> ");
				if (!line || ft_strcmp(line, redir->target) == 0)
				{
					free(line);
					break;
				}
				write(pipe_fds[1], line, ft_strlen(line));
				write(pipe_fds[1], "\n", 1);
				free(line);
			}
			close(pipe_fds[1]);
			dup2(pipe_fds[0], STDIN_FILENO);
			close(pipe_fds[0]);
		}
		else
		{
			fd = open_redir_fd(redir);
			if (fd < 0)
			{
				if (!shell->err_print)
					perror(redir->target);
				shell->err_print = true;
				return (-1);
			}
			if (redir->type == REDIR_INPUT)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
}
