/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:12:20 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/09 22:45:29 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all_pipes(int **pipes, int count)
{
	int	i;

	if (!pipes || count <= 0)
		return ;
	i = 0;
	while (i < count - 1)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}

void	free_pipes(t_pipeinfo *info)
{
	int	i;

	if (!info || !info->pipes)
		return ;
	i = 0;
	while (i < info->count - 1)
	{
		if (info->pipes[i])
		{
			close(info->pipes[i][0]);
			close(info->pipes[i][1]);
			free(info->pipes[i]);
		}
		i++;
	}
	free(info->pipes);
	info->pipes = NULL;
}

void	free_info(t_pipeinfo *info)
{
	//int	i;

	//i = 0;
	if (!info)
		return ;
	if (info->pipes)
		free_pipes(info);
	if (info->pids)
	{
		free(info->pids);
		info->pids = NULL;
	}
	info->count = 0;
	info->idx = 0;
}

int	count_pipeline_commands(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_PIPELINE)
		return (count_pipeline_commands(node->left)
			+ count_pipeline_commands(node->right));
	return (1);
}

int	**create_pipes(int count)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (count - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) < 0)
		{
			while (--i >= 0)
				free(pipes[i]);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
