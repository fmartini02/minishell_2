/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:45:21 by francema          #+#    #+#             */
/*   Updated: 2025/05/12 16:54:08 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmd_info(t_cmd_info *cmd_info)
{
	int			i;
	t_cmd_info	*next;

	while (cmd_info)
	{
		i = 0;
		free(cmd_info->cmd_name);
		if (cmd_info->cmd_args)
		{
			while (cmd_info->cmd_args[i])
			{
				free(cmd_info->cmd_args[i]);
				i++;
			}
			free(cmd_info->cmd_args);
		}
		next = cmd_info->next;
		free(cmd_info);
		cmd_info = next;
	}
}

void	ft_fatal_memerr(t_mini *shell)
{
	ft_putstr_fd("Error: ", 2);
	perror("malloc");
	free(shell->input);
	ft_lstclear(&shell->env, free);
	ft_lstclear(&shell->tok_input, free);
	ft_free_cmd_info(shell->cmd_info);
	exit(EXIT_FAILURE);
}
