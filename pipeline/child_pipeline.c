/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:05:38 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/04 19:06:12 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	input_redir_exists(t_redirection *r)
{
	while (r)
	{
		if (r->type == REDIR_INPUT || r->type == REDIR_HEREDOC)
			return (true);
		r = r->next;
	}
	return (false);
}

static bool	output_redir_exists(t_redirection *r)
{
	while (r)
	{
		if (r->type == REDIR_OUTPUT || r->type == REDIR_APPEND)
			return (true);
		r = r->next;
	}
	return (false);
}

static void	redirect_pipeline_io(t_exec_unit *unit, int **pipes,
	int idx, int count)
{
	if (idx > 0)
	{
		if (!input_redir_exists(unit->redirs))
		{
			if (dup2(pipes[idx - 1][0], STDIN_FILENO) == -1)
				perror("dup2 stdin");
		}
		close(pipes[idx - 1][0]);
	}
	if (idx < count - 1)
	{
		if (!output_redir_exists(unit->redirs))
		{
			if (dup2(pipes[idx][1], STDOUT_FILENO) == -1)
				perror("dup2 stdout");
		}
		close(pipes[idx][1]);
	}
}

void	child_pipeline(t_ast_node *node, t_pipeinfo *info)
{
	t_exec_unit	*unit;

	unit = extract_exec_units(node);
	if (!unit)
		exit(EXIT_FAILURE);
	redirect_pipeline_io(unit, info->pipes, info->idx, info->count);
	if (apply_redirections(unit, info->shell) != 0)
	{
		free_exec_unit(unit);
		exit(EXIT_FAILURE);
	}
	close_all_pipes(info->pipes, info->count);
	if (unit->argv && is_builtin(unit->argv[0]))
		exit(execute_builtin(unit, info->shell, false));
	child_process(unit, info->shell);
	free_exec_unit(unit);
	exit(EXIT_SUCCESS);
}
