/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:09:14 by mdalloli          #+#    #+#             */
/*   Updated: 2025/06/25 18:04:07 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	setup_pipeline(int count, int ***pipes, pid_t **pids)
{
	if (count >= 1)
	{
		*pipes = create_pipes(count);
		if (!*pipes)
			return (perror("pipe"), -1);
	}
	*pids = malloc(sizeof(pid_t) * count);
	if (!*pids)
		return (perror("malloc pids"), -1);
	return (0);
}

static int	fork_pipeline_procs(t_ast_node *cmds, t_mini *shell,
	int **pipes, pid_t *pids)
{
	int			idx;
	t_ast_node	*curr;

	idx = 0;
	curr = cmds;
	while (curr)
	{
		pids[idx] = fork();
		if (pids[idx] < 0)
			return (perror("fork"), -1);
		else if (pids[idx] == 0)
			child_pipeline(curr, shell, pipes, idx,
				count_pipeline_commands(cmds));
		curr = curr->next;
		idx++;
	}
	return (0);
}

/* static void	wait_for_pipeline(pid_t *pids, int count, t_mini *shell)
{
	int	status;
	int	i;

	i = -1;
	while (++i < count - 1)
		waitpid(pids[i], NULL, 0);
	waitpid(pids[count - 1], &status, 0);
	if (WIFEXITED(status))
		shell->last_exit_code = WEXITSTATUS(status);
	else
		shell->last_exit_code = 128 + WTERMSIG(status);
}

void	execute_pipeline(t_ast_node *cmds, t_mini *shell)
{
	int		count;
	int		**pipes;
	pid_t	*pids;

	count = count_pipeline_commands(cmds);
	pipes = NULL;
	if (count == 0 || setup_pipeline(count, &pipes, &pids) < 0)
		return ;
	write(1, "qua1\n", 5);
	if (fork_pipeline_procs(cmds, shell, pipes, pids) < 0)
	{
		write(1, "qua2\n", 5);
		free(pids);
		return ;
	}
	if (pipes)
	{
		write(1, "qua3\n", 5);
		close_all_pipes(pipes, count);
		free_pipes(pipes, count);
	}
	write(1, "qua4\n", 5);
	wait_for_pipeline(pids, count, shell);
	write(1, "qua5\n", 5);
	free(pids);
} */
void	execute_pipeline(t_ast_node *cmds, t_mini *shell)
{
    int		count;
    int		**pipes;
    pid_t	*pids;
    int		status;
    int		i;
    int		last_status = 0;

    count = count_pipeline_commands(cmds);
    pipes = NULL;
    if (count == 0 || setup_pipeline(count, &pipes, &pids) < 0)
        return ;
    if (fork_pipeline_procs(cmds, shell, pipes, pids) < 0)
    {
        free(pids);
        return ;
    }
    if (pipes)
    {
        close_all_pipes(pipes, count);
        free_pipes(pipes, count);
    }
    i = 0;
    while (i < count)
    {
        if (waitpid(pids[i], &status, 0) > 0)
        {
            if (i == count - 1)
                last_status = status;
        }
        i++;
    }
    if (WIFEXITED(last_status))
        shell->last_exit_code = WEXITSTATUS(last_status);
    else if (WIFSIGNALED(last_status))
        shell->last_exit_code = 128 + WTERMSIG(last_status);
    free(pids);
}
