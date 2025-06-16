#include "minishell.h"

/* Execution builtins */
int	execute_builtin(t_exec_unit *unit, t_mini *shell)
{
	char	**args;

	args = unit->argv;
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(shell);
	else if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(shell);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(shell);
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(shell);
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(shell);
	else if (ft_strcmp(args[0], "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(shell, NULL);
	return (shell->last_exit_code);
}

static int	handle_critical_builtin(t_exec_unit *unit, t_mini *shell)
{
	if (!is_builtin(unit->argv[0]))
		return (0);
	if (ft_strcmp(unit->argv[0], "cd") != 0
		&& ft_strcmp(unit->argv[0], "export") != 0
		&& ft_strcmp(unit->argv[0], "unset") != 0
		&& ft_strcmp(unit->argv[0], "exit") != 0)
		return (0);
	if (apply_redirections(shell) != 0)
	{
		shell->last_exit_code = 1;
		return (1);
	}
	shell->last_exit_code = execute_builtin(unit, shell);
	return (1);
}

static void	child_process(t_exec_unit *unit, t_mini *shell)
{
	if (apply_redirections(shell) != 0)
		exit(1);
	if (is_builtin(unit->argv[0]))
		exit(execute_builtin(unit, shell));
	execvp(unit->argv[0], unit->argv);
	perror("execvp failed");
	exit(127);
}

/* Executes a single execution unit (command) in the shell.
If the command is a critical built-in (cd, export, unset, exit),
it is executed directly in the parent process after applying redirections
Otherwise, a child process is forked:
- In the child: apply redirections, execute the built-in or external command
- In the parent: wait for the child and store its exit code */
void	execute_exec_unit(t_exec_unit *unit, t_mini *shell)
{
	pid_t	pid;
	int		status;

	if (!unit || !unit->argv || !unit->argv[0])
		return ;
	if (handle_critical_builtin(unit, shell))
		return ;
	pid = fork();
	if (pid == 0)
		child_process(unit, shell);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_code = WEXITSTATUS(status);
	}
	else
	{
		perror("fork failed");
		shell->last_exit_code = 1;
	}
}

/* Recursively executes an AST node based on its type */
void	execute_ast(t_ast_node *node, t_mini *shell)
{
	t_exec_unit	*unit;

	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		unit = extract_exec_unit(node);
		if (unit)
		{
			execute_exec_unit(unit, shell);
			free_exec_unit(unit);
		}
	}
	/* else if (node->type == NODE_PIPELINE)
	{
		// execute_pipeline
	} */
	else if (node->type == NODE_AND)
	{
		execute_ast(node->left, shell);
		if (shell->last_exit_code == 0)
			execute_ast(node->right, shell);
	}
	else if (node->type == NODE_OR)
	{
		execute_ast(node->left, shell);
		if (shell->last_exit_code != 0)
			execute_ast(node->right, shell);
	}
}
