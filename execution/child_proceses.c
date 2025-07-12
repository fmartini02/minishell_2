/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proceses.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:11:14 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 18:36:53 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_redirs_and_builtin(
	t_exec_unit *unit, t_mini *shell, t_pipinfo *info)
{
	if (apply_redirections(unit, shell) != 0)
		cleanup_shell(shell, 1);
	if (is_builtin(unit->argv[0]))
		exit(execute_builtin(unit, shell, info));
}

void	err_cmd_not_found(t_exec_unit *unit)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(unit->argv[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

static void	exec_external_command(
	t_exec_unit *unit, t_mini *shell, t_pipinfo *info)
{
	char	*cmd_path;
	char	**envp;

	cmd_path = get_path_command(shell, unit->argv[0]);
	if (!cmd_path)
	{
		err_cmd_not_found(unit);
		if (info)
			free_info(info);
		cleanup_shell(shell, 127);
	}
	envp = env_list_to_array(shell->env);
	if (!envp)
	{
		free(cmd_path);
		exit(1);
	}
	execve(cmd_path, unit->argv, envp);
	perror("execve failed");
	free(cmd_path);
	free_mat(envp);
	cleanup_shell(shell, 127);
}

void	child_process(t_exec_unit *unit, t_mini *shell, t_pipinfo *info)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!unit || !unit->argv || !unit->argv[0])
		exit(0);
	handle_redirs_and_builtin(unit, shell, info);
	exec_external_command(unit, shell, info);
}
