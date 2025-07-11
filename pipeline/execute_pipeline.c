/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:09:14 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/11 22:54:24 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	setup_pipeline(t_pipeinfo *info, int count)
{
	if (count >= 1)
	{
		info->pipes = create_pipes(count);
		if (!info->pipes)
			return (perror("pipe"), -1);
	}
	info->pids = malloc(sizeof(pid_t) * count);
	if (!info->pids)
		return (perror("malloc pids"), -1);
	info->idx = 0;
	return (0);
}

static void	fork_recursive(t_ast_node *node, t_pipeinfo *info)
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
		info->pids[info->idx] = fork();
		if (info->pids[info->idx] < 0)
			perror("fork");
		else if (info->pids[info->idx] == 0)
			child_pipeline(node, info);
		info->idx++;
	}
}

static void	wait_all(t_pipeinfo *info)
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
	t_pipeinfo	info;

	handle_eventual_heredoc(cmds, shell);
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
