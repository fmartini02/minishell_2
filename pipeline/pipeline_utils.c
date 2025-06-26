/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:12:20 by mdalloli          #+#    #+#             */
/*   Updated: 2025/06/26 11:42:25 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		fprintf(stderr, "[%d] chiudo pipe[%d][0]=%d pipe[%d][1]=%d\n", getpid(), i, pipes[i][0], i, pipes[i][1]);
		i++;
	}
}

void	free_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	count_pipeline_commands(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_PIPELINE)
		return count_pipeline_commands(node->left) + count_pipeline_commands(node->right);
	return 1;
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
