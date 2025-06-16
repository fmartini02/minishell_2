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
}
