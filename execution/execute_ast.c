/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:06:49 by francema          #+#    #+#             */
/*   Updated: 2025/07/11 23:10:51 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	exec_unit_with_only_redirs(t_exec_unit *unit, t_mini *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		shell->last_exit_code = 1;
		return ;
	}
	if (pid == 0)
	{
		if (apply_redirections(unit, shell) != 0)
			cleanup_shell(shell, 1);
		cleanup_shell(shell, 0);
	}
	else
		wait_for_child(pid, shell);
}

static void	exec_external_command(t_exec_unit *unit, t_mini *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		shell->last_exit_code = 1;
		return ;
	}
	if (pid == 0)
		child_process(unit, shell, NULL);
	else
		wait_for_child(pid, shell);
}

void	execute_exec_unit(t_exec_unit *unit, t_mini *shell)
{
	if (!unit)
		return ;
	if ((!unit->argv || !unit->argv[0]) && unit->redirs)
	{
		exec_unit_with_only_redirs(unit, shell);
		return ;
	}
	if (is_cd_export_unset_exit(unit->argv[0]))
	{
		shell->last_exit_code = execute_builtin(unit, shell, NULL);
		return ;
	}
	exec_external_command(unit, shell);
}

// /* Recursively executes an AST node based on its type */
// static void	execute_logic(t_ast_node *node, t_mini *shell)
// {
// 	if (node->type == NODE_AND)
// 	{
// 		execute_ast(node->left, shell);
// 		if (shell->last_exit_code == 0)
// 			execute_ast(node->right, shell);
// 	}
// 	else if (node->type == NODE_OR)
// 	{
// 		execute_ast(node->left, shell);
// 		if (shell->last_exit_code != 0)
// 			execute_ast(node->right, shell);
// 	}
// }
void	execute_ast(t_ast_node *node, t_mini *shell)
{
	t_exec_unit	*unit;

	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		handle_eventual_heredoc(node, shell);
		unit = extract_exec_units(node);
		shell->unit = unit;
		if (unit)
		{
			execute_exec_unit(unit, shell);
			if (shell->unit)
			{
				free_exec_unit(unit);
				shell->unit = NULL;
			}
			shell->err_print = false;
		}
		if (shell->last_exit_code != 0)
			return ;
		close_all_heredoc_fds(node);
	}
	else if (node->type == NODE_PIPELINE)
		execute_pipeline(node, shell);
}
	// else
	// 	execute_logic(node, shell);
