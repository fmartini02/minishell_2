/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:19:07 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/01 10:19:57 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Handles a fatal memory allocation error.
Frees all shell resources, prints an error message
and terminates the program */
void	ft_fatal_memerr(t_mini *shell)
{
	ft_putstr_fd("Error: malloc failure \n", 2);
	cleanup_shell(shell, EXIT_FAILURE);
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

void	cleanup_shell(t_mini *shell, int exit_code)
{
	if (!shell)
		exit(exit_code);
	if (shell->env && exit_code >= 0)
	{
		ft_lstclear(&shell->env, free);
		shell->env = NULL;
	}
	if (shell->unit)
	{
		free_exec_unit(shell->unit);
		shell->unit = NULL;
	}
	if (shell->ast_root)
	{
		//printf("qui\n");
		free_ast(shell->ast_root);
		shell->ast_root = NULL;
	}
	if (shell->tok_input)
	{
		//printf("qui2\n");
		free_tok_lst(shell->tok_input);
		shell->tok_input = NULL;
	}
	if (shell->cmd_info)
	{
		free_cmd_info(shell->cmd_info);
		shell->cmd_info = NULL;
	}
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->prompt)
	{
		free(shell->prompt);
		shell->prompt = NULL;
	}
	if (exit_code >= 0)
		exit(exit_code);
}
