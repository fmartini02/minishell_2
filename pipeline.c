#include "minishell.h"

static int	count_pipeline_commands(t_ast_node *cmd_list)
{
	int count = 0;
	while (cmd_list)
	{
		count++;
		cmd_list = cmd_list->next;
	}
	return count;
}

static bool input_redir_exists(t_redirection *r)
{
	while (r)
	{
		if (r->type == REDIR_INPUT || r->type == REDIR_HEREDOC)
			return true;
		r = r->next;
	}
	return false;
}

static bool output_redir_exists(t_redirection *r)
{
	while (r)
	{
		if (r->type == REDIR_OUTPUT || r->type == REDIR_APPEND)
			return true;
		r = r->next;
	}
	return false;
}

static int	**create_pipes(int count)
{
	int	**pipes = malloc(sizeof(int *) * (count - 1));
	if (!pipes)
		return (NULL);
	for (int i = 0; i < count - 1; i++)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) < 0)
			return (NULL);
	}
	return (pipes);
}

static void	close_all_pipes(int **pipes, int count)
{
	for (int i = 0; i < count - 1; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

static void	free_pipes(int **pipes, int count)
{
	for (int i = 0; i < count - 1; i++)
		free(pipes[i]);
	free(pipes);
}

static void	child_pipeline(t_ast_node *node, t_mini *shell, int **pipes, int i, int count)
{
	t_exec_unit	*unit = extract_exec_unit(node);
	if (!unit)
		exit(1);

	if (apply_redirections(unit, shell) != 0)
		exit(1);

	// Se la redirezione non ha già fatto dup2 su stdin/stdout, applica le pipe
	if (i > 0 && !input_redir_exists(unit->redirs))
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < count - 1 && !output_redir_exists(unit->redirs))
		dup2(pipes[i][1], STDOUT_FILENO);

	close_all_pipes(pipes, count);

	if (is_builtin(unit->argv[0]))
		exit(execute_builtin(unit, shell));

	execvp(unit->argv[0], unit->argv);
	perror("execvp failed");
	exit(127);
}

void	execute_pipeline(t_ast_node *cmd_list, t_mini *shell)
{
	int		count = count_pipeline_commands(cmd_list);
	int		**pipes = create_pipes(count);
	pid_t	*pids = malloc(sizeof(pid_t) * count);
	int		i = 0;
	t_ast_node *curr = cmd_list;

	if (!pipes || !pids)
	{
		perror("pipe or malloc");
		exit(1);
	}
	while (curr)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			child_pipeline(curr, shell, pipes, i, count);
		else if (pids[i] < 0)
			perror("fork");
		curr = curr->next;
		i++;
	}
	close_all_pipes(pipes, count);

	for (int j = 0; j < count; j++)
		waitpid(pids[j], &i, 0); // puoi salvare WEXITSTATUS se vuoi
	shell->last_exit_code = WEXITSTATUS(i);
	free_pipes(pipes, count);
	free(pids);
}
