#include "minishell.h"

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static char *ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char *tmp;
	char *res;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
}

char	*get_path_command(t_mini *shell, const char *cmd)
{
	char	**paths;
	char	*full_path;
	char	*path_var;
	int		i;

	if (!cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_var = get_env_value(shell, "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin3(paths[i], "/", cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}


/* Execution builtins */
int	execute_builtin(t_exec_unit *unit, t_mini *shell)
{
	char	**args;

	args = unit->argv;
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(args, shell);
	else if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args, shell);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(shell, args);
	else if (ft_strcmp(args[0], "env") == 0)
		ft_env(shell, args);
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(shell, args);
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(shell, args);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(shell, args);
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
	if (apply_redirections(unit, shell) != 0)
	{
		shell->last_exit_code = 1;
		return (1);
	}
	shell->last_exit_code = execute_builtin(unit, shell);
	return (1);
}

static void	child_process(t_exec_unit *unit, t_mini *shell)
{
	char *cmd_path;

	if (apply_redirections(unit, shell) != 0)
		exit(1);
	if (is_builtin(unit->argv[0]))
		exit(execute_builtin(unit, shell));

	cmd_path = get_path_command(shell, unit->argv[0]);
	if (!cmd_path)
	{
		ft_putstr_fd(unit->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	char **envp = env_list_to_array(shell->env);
	if (!envp)
	{
		perror(("env_list_to_array failed"));
		free(cmd_path);
		exit(1);
	}
	execve(cmd_path, unit->argv, envp);
	perror("execve failed");
	free_split(envp);
	free(cmd_path);
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
	{
		printf("execute_ast: nodo NULL\n");
		return ;
	}
	if (node->type == NODE_CMD)
	{
		unit = extract_exec_unit(node);
		if (unit)
		{
			execute_exec_unit(unit, shell);
			free_exec_unit(unit);
		}
	}
	else if (node->type == NODE_PIPELINE)
	{
		printf("execute_ast: nodo PIPELINE\n");
		execute_pipeline(node, shell);
	}
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
	else
		printf("execute_ast: tipo nodo sconosciuto (%d)\n", node->type);
}
