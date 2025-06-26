/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:23:20 by mdalloli          #+#    #+#             */
/*   Updated: 2025/06/26 11:21:28 by mdalloli         ###   ########.fr       */
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

/* int	apply_redirections(t_exec_unit *unit, t_mini *shell)
{
	t_redirection	*redir;
	int				fd;
	int				pipe_fds[2];
	char			*line;
	int				last_in;

	redir = unit->redirs;
	last_in = -1;
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
					break ;
				}
				write(pipe_fds[1], line, ft_strlen(line));
				write(pipe_fds[1], "\n", 1);
				free(line);
			}
			close(pipe_fds[1]);
			if (last_in != -1)
				close(last_in);
			dup2(pipe_fds[0], STDIN_FILENO);
			last_in = pipe_fds[0];
		}
		else if (redir->type == REDIR_INPUT)
		{
			fd = open_redir_fd(redir);
			if (fd < 0)
			{
				if (!shell->err_print)
					perror(redir->target);
				shell->err_print = true;
				return (-1);
			}
			if (last_in != -1)
				close(last_in);
			dup2(fd, STDIN_FILENO);
			last_in = fd;
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
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	if (last_in != -1)
		close(last_in);
	return (0);
} */

static int	handle_heredoc(t_redirection *redir, int *last_in)
{
    int		pipe_fds[2];
    char	*line;

    if (pipe(pipe_fds) == -1)
        return (perror("pipe"), -1);
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, redir->target) == 0)
        {
            free(line);
            break ;
        }
        write(pipe_fds[1], line, ft_strlen(line));
        write(pipe_fds[1], "\n", 1);
        free(line);
    }
    close(pipe_fds[1]);
    if (*last_in != -1 && *last_in != STDIN_FILENO)
        close(*last_in);
    if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
        perror("dup2 heredoc");
    close(pipe_fds[0]); // <--- CHIUDI SEMPRE QUI!
    *last_in = -1;      // <--- NON SERVE PIU' GESTIRE last_in PER HEREDOC
    return (0);
}

static int	handle_input_redirection(t_redirection *redir, t_mini *shell,
	int *last_in)
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
	if (*last_in != -1)
		close(*last_in);
	dup2(fd, STDIN_FILENO);
	*last_in = fd;
	return (0);
}

static int	handle_output_redirection(t_redirection *redir, t_mini *shell)
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
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redirections(t_exec_unit *unit, t_mini *shell)
{
    t_redirection	*redir;
    int				last_in;

    redir = unit->redirs;
    last_in = -1;
    while (redir)
    {
        if (redir->type == REDIR_HEREDOC
            && handle_heredoc(redir, &last_in) < 0)
            return (-1);
        else if (redir->type == REDIR_INPUT
            && handle_input_redirection(redir, shell, &last_in) < 0)
            return (-1);
        else if ((redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
            && handle_output_redirection(redir, shell) < 0)
            return (-1);
        redir = redir->next;
    }
    if (last_in != -1 && last_in != STDIN_FILENO)
        close(last_in);
    return (0);
}
