/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:19:07 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/12 15:40:36 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Handles a fatal memory allocation error.
Frees all shell resources, prints an error message
and terminates the program */
void	ft_fatal_memerr(t_mini *shell)
{
	ft_putstr_fd("Error: malloc failure \n", 2);
	cleanup_shell(shell, EXIT_FAILURE);
}

void	free_env(t_mini *shell)
{
	if (shell->env)
	{
		ft_lstclear(&shell->env, free);
		shell->env = NULL;
	}
}

void	free_tok_lst(t_tok_lst *head)
{
	t_tok_lst	*node;
	t_tok_lst	*next_node;

	node = head;
	while (node)
	{
		next_node = node->next;
		if (node->content)
			free(node->content);
		if (node->tok_name)
			free(node->tok_name);
		free(node);
		node = next_node;
	}
	node = NULL;
}

void	free_info(t_pipeinfo *info)
{
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

/* Frees all memory associated with a t_exec_unit structure.
This includes the argument vector (argv) and the structure itself.
If the unit is NULL, the function does nothing.*/
void	free_exec_unit(t_exec_unit *unit)
{
	int	i;

	if (!unit)
		return ;
	if (unit->argv)
	{
		i = 0;
		while (unit->argv[i])
		{
			free(unit->argv[i]);
			i++;
		}
		free(unit->argv);
	}
	free(unit);
}
