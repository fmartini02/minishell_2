/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:29:09 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/07 18:53:37 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Execution builtins */
int	execute_builtin(t_exec_unit *unit, t_mini *shell, bool is_parent)
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
		ft_exit(shell, args, is_parent);
	cleanup_shell(shell, shell->last_exit_code);
	return (shell->last_exit_code);
}

int	handle_critical_builtin(t_exec_unit *unit, t_mini *shell)
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
	shell->last_exit_code = execute_builtin(unit, shell, true);
	return (1);
}
