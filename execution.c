/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:22:30 by mdalloli          #+#    #+#             */
/*   Updated: 2025/06/26 14:19:55 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_exec_unit *unit, t_mini *shell)
{
	char	*cmd_path;
	char	**envp;

	if (apply_redirections(unit, shell) != 0)
		exit(1);
	if (is_builtin(unit->argv[0]))
		exit(execute_builtin(unit, shell));
	cmd_path = get_path_command(shell, unit->argv[0]);
	if (!cmd_path)
		exit_command_not_found(unit);
	envp = env_list_to_array(shell->env);
	if (!envp)
	{
		perror("env_list_to_array failed");
		free(cmd_path);
		exit(1);
	}
	execve(cmd_path, unit->argv, envp);
	perror("execve failed");
	free_split(envp);
	free(cmd_path);
	exit(127);
}

/**/
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
static void	execute_logic(t_ast_node *node, t_mini *shell)
{
	if (node->type == NODE_AND)
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

void	execute_ast(t_ast_node *node, t_mini *shell)
{
	t_exec_unit	*unit;

	if (!node)
		return ((void)printf("execute_ast: nodo NULL\n")); //////////////////////////
	if (node->type == NODE_CMD)
	{
		prepare_heredocs(node);
		unit = extract_exec_unit(node);
		if (unit)
		{
			execute_exec_unit(unit, shell);
			free_exec_unit(unit);
		}
	}
	else if (node->type == NODE_PIPELINE)
		execute_pipeline(node, shell);
	else
		execute_logic(node, shell);
}
