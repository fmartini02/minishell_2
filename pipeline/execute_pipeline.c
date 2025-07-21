/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:09:14 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/21 15:20:20 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	setup_pipeline(t_pipinfo *info, int count)
{
	int	i;

	i = count;
	if (count >= 1)
	{
		info->pipes = create_pipes(count);
		if (!info->pipes)
			return (perror("pipe"), -1);
	}
	info->pids = malloc(sizeof(pid_t) * count);
	if (!info->pids)
		return (perror("malloc pids"), -1);
	while (i > 0)
	{
		info->pids[i - 1] = 0;
		i--;
	}
	info->idx = 0;
	return (0);
}

static void	fork_recursive(t_ast_node *node, t_pipinfo *info)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPELINE)
	{
		fork_recursive(node->left, info);
		fork_recursive(node->right, info);
	}
	else
	{
		if (g_sig_code == false)
			handle_eventual_heredoc(node, info->shell);
		if (g_sig_code == true)
		{
			close_all_heredoc_fds(node);
			return ;
		}
		info->pids[info->idx] = fork();
		if (info->pids[info->idx] < 0)
			perror("fork");
		else if (info->pids[info->idx] == 0)
			child_pipeline(node, info);
		info->idx++;
	}
}

static void	wait_all(t_pipinfo *info)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < info->count)
	{
		if (waitpid(info->pids[i], &status, 0) > 0)
		{
			if (i == info->count - 1)
				last_status = status;
		}
		i++;
	}
	if (WIFEXITED(last_status))
		info->shell->last_exit_code = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status))
		info->shell->last_exit_code = 128 + WTERMSIG(last_status);
}

void	execute_pipeline(t_ast_node *cmds, t_mini *shell)
{
	t_pipinfo	info;

	// handle_eventual_heredoc(cmds, shell);
	info.count = count_pipeline_commands(cmds);
	info.shell = shell;
	if (info.count == 0 || setup_pipeline(&info, info.count) < 0)
		return ;
	fork_recursive(cmds, &info);
	close_all_pipes(info.pipes, info.count);
	wait_all(&info);
	free_info(&info);
	close_all_heredoc_fds(cmds);
}
