#include "../minishell.h"

static int	setup_pipeline(int count, int ***pipes, pid_t **pids)
{
	if (count > 1)
	{
		*pipes = create_pipes(count);
		if (!*pipes)
			return (perror("pipe"), -1);
	}
	*pids = malloc(sizeof(pid_t) * count);
	if (!*pids)
		return (perror("malloc pids"), -1);
	return (0);
}

static int	fork_pipeline_procs(t_ast_node *cmds, t_mini *shell, int **pipes, pid_t *pids)
{
	int			idx = 0;
	t_ast_node	*curr = cmds;

	while (curr)
	{
		pids[idx] = fork();
		if (pids[idx] < 0)
			return (perror("fork"), -1);
		else if (pids[idx] == 0)
			child_pipeline(curr, shell, pipes, idx, count_pipeline_commands(cmds));
		curr = curr->next;
		idx++;
	}
	return (0);
}

void	execute_pipeline(t_ast_node *cmds, t_mini *shell)
{
	int		count = count_pipeline_commands(cmds);
	int		**pipes = NULL;
	pid_t	*pids;
	int		status, i;

	if (count == 0 || setup_pipeline(count, &pipes, &pids) < 0)
		return ;
	if (fork_pipeline_procs(cmds, shell, pipes, pids) < 0)
		return (free(pids));
	if (pipes)
		close_all_pipes(pipes, count), free_pipes(pipes, count);
	i = -1;
	while (++i < count - 1)
		waitpid(pids[i], NULL, 0);
	waitpid(pids[count - 1], &status, 0);
	shell->last_exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : 128 + WTERMSIG(status);
	free(pids);
}
