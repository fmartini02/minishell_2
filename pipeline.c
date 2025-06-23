 #include "minishell.h"

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
		{
			while (--i >= 0)
				free(pipes[i]);
			free(pipes);
			return (NULL);
		}
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

static void	child_pipeline(t_ast_node *node, t_mini *shell,
						int **pipes, int idx, int count)
{
	t_exec_unit	*unit;
	char		*cmd_path;

	unit = extract_exec_unit(node);
	if (!unit)
		exit(1);
	if (idx > 0 && !input_redir_exists(unit->redirs))
	{
		if (dup2(pipes[idx - 1][0], STDIN_FILENO) < 0)
		{
			perror("dup2 stdin");
			exit(1);
		}
	}
	if (idx < count - 1 && !output_redir_exists(unit->redirs))
	{
		if (dup2(pipes[idx][1], STDOUT_FILENO) < 0)
		{
			perror("dup2 stdout");
			exit(1);
		}
	}
	close_all_pipes(pipes, count);
	if (apply_redirections(unit, shell) != 0)
		exit(1);
	if (!unit->argv || !unit->argv[0])
		exit(0);
	if (is_builtin(unit->argv[0]))
		exit(execute_builtin(unit, shell));
	cmd_path = get_path_command(shell, unit->argv[0]);
	if (!cmd_path)
	{
		ft_putstr_fd(unit->argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	char **envp = env_list_to_array(shell->env);
	if (!envp)
	{
		perror("env_list_to_array failed");
		free(cmd_path);
		exit(1);
	}
	execve(cmd_path, unit->argv, shell->envp);
	perror(cmd_path);
	free_split(envp);
	free(cmd_path);
	exit(127);
}

void	execute_pipeline(t_ast_node *cmd_list, t_mini *shell)
{
	int			count;
	int			**pipes;
	pid_t		*pids;
	int			idx;
	int			status;
	t_ast_node	*curr;

	count = count_pipeline_commands(cmd_list);
	if (count == 0)
		return ;
	pipes = NULL;
	if (count > 1)
	{
		pipes = create_pipes(count);
		if (!pipes)
			return (perror("pipe creation failed"), (void)0);
	}
	pids = malloc(sizeof(pid_t) * count);
	if (!pids)
	{
		perror("malloc pids");
		if (pipes)
			free_pipes(pipes, count);
		return ;
	}
	curr = cmd_list;
	idx = 0;
	while (curr && idx < count)
	{
		pids[idx] = fork();
		if (pids[idx] < 0)
		{
			perror("fork failed");
			while (--idx >= 0)
				waitpid(pids[idx], NULL, 0);
			if (pipes)
			{
				close_all_pipes(pipes, count);
				free_pipes(pipes, count);
			}
			free(pids);
			shell->last_exit_code = 1;
			return ;
		}
		else if (pids[idx] == 0)
			child_pipeline(curr, shell, pipes, idx, count);
		curr = curr->next;
		idx++;
	}
	if (pipes)
	{
		close_all_pipes(pipes, count);
		free_pipes(pipes, count);
	}
	idx = 0;
	while (idx < count - 1)
		waitpid(pids[idx++], NULL, 0);
	waitpid(pids[count - 1], &status, 0);
	if (WIFEXITED(status))
		shell->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_exit_code = 128 + WTERMSIG(status);
	free(pids);
}
