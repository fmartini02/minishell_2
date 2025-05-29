#include "minishell.h"

int	apply_redirection(t_mini *shell)
{
	t_redirection	*redir = shell->cmd_info->redirections;
	int				fd;

	while (redir)
	{
		if (redir->type == REDIR_INPUT)
			fd = open(redir->target, O_RDONLY);
		else if (redir->type == REDIR_OUTPUT)
			fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == REDIR_APPEND)
			fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == REDIR_HEREDOC)
			// handle_heredoc
		if (fd < 0)
		{
			if (!shell->err_print)
			{
				perror(redir->target);
				shell->err_print = true;
			}
			shell->last_exit_code = 1;
			return (-1);
		}
		if ((redir->type == REDIR_INPUT || redir->type == REDIR_HEREDOC) && dup2(fd, STDIN_FILENO) == -1)
			return (-1);
		if ((redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND) && dup2(fd, STDOUT_FILENO) == -1)
			return (-1);
		close(fd);
		redir = redir->next;
	}
	return (0);
}
