/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:19:07 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/01 14:04:54 by mdalloli         ###   ########.fr       */
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
