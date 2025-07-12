/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:29:09 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/12 14:44:19 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Execution builtins */
int	chose_builtin(
	t_exec_unit *unit, t_mini *shell, bool is_parent, t_pipeinfo *info)
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
	if (info)
		free_info(info);
	if (is_parent == true)
		cleanup_shell(shell, shell->last_exit_code);
	return (shell->last_exit_code);
}

bool	is_cd_export_unset_exit(const char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	execute_builtin(t_exec_unit *unit, t_mini *shell, t_pipeinfo *info)
{
	if (!is_builtin(unit->argv[0]))
		return (0);
	if (apply_redirections(unit, shell) != 0)
	{
		shell->last_exit_code = 1;
		return (1);
	}
	if (is_cd_export_unset_exit(unit->argv[0]))
		shell->last_exit_code = chose_builtin(unit, shell, false, info);
	else
		shell->last_exit_code = chose_builtin(unit, shell, true, info);
	return (1);
}
