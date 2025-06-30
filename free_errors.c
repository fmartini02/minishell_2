/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:19:07 by mdalloli          #+#    #+#             */
/*   Updated: 2025/06/30 15:58:33 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Handles a fatal memory allocation error.
Frees all shell resources, prints an error message
and terminates the program */
void	ft_fatal_memerr(t_mini *shell)
{
	ft_putstr_fd("Error: malloc failure \n", 2);
	free(shell->input);
	ft_lstclear(&shell->env, free);
	free_tok_lst(shell->tok_input);
	exit(EXIT_FAILURE);
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
	if (shell->env)
		ft_lstclear(&shell->env, free);
	if (shell->ast_root)
		free_ast(shell->ast_root);
	if (shell->tok_input)
		free_tok_lst(shell->tok_input);
	if (shell->cmd_info)
		free_cmd_info(shell->cmd_info);
	if (shell->input)
		free(shell->input);
	free(shell->prompt);
	if (exit_code > 0)
		exit(exit_code);
}

