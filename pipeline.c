 #include "minishell.h"
/*
static int	count_pipeline_commands(t_ast_node *cmd_list)
{
	int	count;

	count = 0;
	while (cmd_list)
	{
		count++;
		cmd_list = cmd_list->next;
	}
	return (count);
}

static bool	input_redir_exists(t_redirection *r)
{
	while (r)
	{
		if (r->type == REDIR_INPUT || r->type == REDIR_HEREDOC)
			return (true);
		r = r->next;
	}
	return (false);
}

static bool	output_redir_exists(t_redirection *r)
{
	while (r)
	{
		if (r->type == REDIR_OUTPUT || r->type == REDIR_APPEND)
			return (true);
		r = r->next;
	}
	return (false);
}

static int	**create_pipes(int count)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (count - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) < 0)
			return (NULL);
		i++;
	}
	return (pipes);
}

static void	close_all_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	free_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

static void	child_pipeline(t_ast_node *node, t_mini *shell, int **pipes, int i,
			int count)
{
	t_exec_unit	*unit;

	unit = extract_exec_unit(node);
	if (!unit)
		exit(1);
	if (i > 0 && !input_redir_exists(unit->redirs))
	{
		if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0)
		{
			perror("dup2 stdin failed");
			exit(1);
		}
	}
	if (i < count - 1 && !output_redir_exists(unit->redirs))
	{
		if (dup2(pipes[i][1], STDOUT_FILENO) < 0)
		{
			perror("dup2 stdout failed");
			exit(1);
		}
	}
	close_all_pipes(pipes, count);
	if (apply_redirections(unit, shell) != 0)
		exit(1);
	if (is_builtin(unit->argv[0]))
		exit(execute_builtin(unit, shell));
	execvp(unit->argv[0], unit->argv);
	perror("execvp failed");
	exit(127);
}

void	execute_pipeline(t_ast_node *cmd_list, t_mini *shell)
{
	int		count;
	int		**pipes;
	pid_t	*pids;
	t_ast_node	*curr;
	int		i;
	int		status;

	count = count_pipeline_commands(cmd_list);
	if (count == 0)
		return ;
	pipes = NULL;
	if (count > 1)
	{
		pipes = create_pipes(count);
		if (!pipes)
		{
			perror("pipe allocation");
			exit(1);
		}
	}
	pids = malloc(sizeof(pid_t) * count);
	if (!pids)
	{
		perror("malloc pids");
		if (pipes)
			free_pipes(pipes, count);
		exit(1);
	}
	curr = cmd_list;
	i = 0;
	while (i < count && curr)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("fork failed");
			free(pids);
			if (pipes)
				free_pipes(pipes, count);
			exit(1);
		}
		else if (pids[i] == 0)
			child_pipeline(curr, shell, pipes, i, count);
		curr = curr->next;
		i++;
	}
	if (pipes)
	{
		close_all_pipes(pipes, count);
		free_pipes(pipes, count);
	}
	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	shell->last_exit_code = WEXITSTATUS(status);
	free(pids);
}
 */

void execute_pipeline(t_ast_node *node, t_mini *shell)
{
    if (!node)
        return;

    if (node->type == NODE_PIPELINE)
    {
        int pipe_fd[2];
        pid_t pid1, pid2;
        int status;

        if (pipe(pipe_fd) == -1)
        {
            perror("pipe");
            return;
        }
        pid1 = fork();
        if (pid1 == 0)
        {
            close(pipe_fd[0]);
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(pipe_fd[1]);
            execute_pipeline(node->left, shell);
            exit(shell->last_exit_code);
        }
        else if (pid1 < 0)
        {
            perror("fork");
            return;
        }
        pid2 = fork();
        if (pid2 == 0)
        {
            close(pipe_fd[1]);
            dup2(pipe_fd[0], STDIN_FILENO);
            close(pipe_fd[0]);
            execute_pipeline(node->right, shell);
            exit(shell->last_exit_code);
        }
        else if (pid2 < 0)
        {
            perror("fork");
            return;
        }
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        waitpid(pid1, &status, 0);
        waitpid(pid2, &status, 0);
        shell->last_exit_code = WEXITSTATUS(status);
    }
    else if (node->type == NODE_CMD)
    {
        t_exec_unit *unit = extract_exec_unit(node);
        if (!unit)
            return;
        execute_exec_unit(unit, shell);
        free_exec_unit(unit);
    }
}

