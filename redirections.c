#include "minishell.h"

// here_doc gestito nella pipeline
int	apply_redirections(t_mini *shell)
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
			fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
		{
			fd = -1;
			redir = redir->next;
			continue;
		}

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
}

