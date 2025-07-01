/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:22:30 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/01 14:00:34 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_exec_unit *unit, t_mini *shell)
{
	char	*cmd_path;
	char	**envp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!unit ||!unit->argv || !unit->argv[0])
		exit(0);
	if (apply_redirections(unit, shell) != 0)
		exit(1);
	if (is_builtin(unit->argv[0]))
		exit(execute_builtin(unit, shell));
	cmd_path = get_path_command(shell, unit->argv[0]);
	if (!cmd_path)
	{
		exit_command_not_found(unit);
		cleanup_shell(shell, 127);
	}
	envp = env_list_to_array(shell->env);
	if (!envp)
		return (free(cmd_path), exit(1), (void)0);
	execve(cmd_path, unit->argv, envp);
	perror("execve failed");
	free(cmd_path);
	free_split(envp);
	cleanup_shell(shell, 127);
}

static void	wait_for_child(pid_t pid, t_mini *shell)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		shell->last_exit_code = 128 + sig;
		if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
		else if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
	else if (WIFEXITED(status))
		shell->last_exit_code = WEXITSTATUS(status);
}

void	execute_exec_unit(t_exec_unit *unit, t_mini *shell)
{
	pid_t	pid;

	if (!unit || !unit->argv || !unit->argv[0])
		return ;
	if (handle_critical_builtin(unit, shell))
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		shell->last_exit_code = 1;
		return ;
	}
	if (pid == 0)
		child_process(unit, shell);
	else
		wait_for_child(pid, shell);
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
		return ;
	if (node->type == NODE_CMD)
	{
		prepare_heredocs(node);
		unit = extract_exec_units(node);
		shell->unit = unit;
		if (unit)
		{
			execute_exec_unit(unit, shell);
			if (unit)
			{
				free_exec_unit(unit);
				shell->unit = NULL;
			}
			shell->err_print = false;
		}
		close_all_heredoc_fds(node);
	}
	else if (node->type == NODE_PIPELINE)
		execute_pipeline(node, shell);
	else
		execute_logic(node, shell);
}
