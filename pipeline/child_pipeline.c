#include "../minishell.h"

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

static void	redirect_pipeline_io(t_exec_unit *unit, int **pipes, int idx, int count)
{
	if (idx > 0 && !input_redir_exists(unit->redirs))
		dup2(pipes[idx - 1][0], STDIN_FILENO);
	if (idx < count - 1 && !output_redir_exists(unit->redirs))
		dup2(pipes[idx][1], STDOUT_FILENO);
}

static void	exec_child_command(t_exec_unit *unit, t_mini *shell)
{
	char	*cmd_path;
	char	**envp;

	if (!unit->argv || !unit->argv[0])
		exit(0);
	if (is_builtin(unit->argv[0]))
		exit(execute_builtin(unit, shell));
	cmd_path = get_path_command(shell, unit->argv[0]);
	if (!cmd_path)
		ft_putendl_fd(": command not found", 2), exit(127);
	envp = env_list_to_array(shell->env);
	if (!envp)
		perror("env"), free(cmd_path), exit(1);
	execve(cmd_path, unit->argv, envp);
	perror(cmd_path);
	free_split(envp);
	free(cmd_path);
	exit(127);
}

void	child_pipeline(t_ast_node *node, t_mini *shell, int **pipes, int idx, int count)
{
	t_exec_unit	*unit;

	unit = extract_exec_unit(node);
	if (!unit)
		exit(1);
	redirect_pipeline_io(unit, pipes, idx, count);
	close_all_pipes(pipes, count);
	if (apply_redirections(unit, shell) != 0)
		exit(1);
	exec_child_command(unit, shell);
}
