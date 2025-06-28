/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:23:20 by mdalloli          #+#    #+#             */
/*   Updated: 2025/06/26 16:37:02 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* here_doc gestito nella pipeline */
static int	apply_redir_list(t_redirection *r, t_mini *shell, int *last_in)
{
	while (r)
	{
		if (r->type == REDIR_HEREDOC)
		{
			if (handle_heredoc(r) < 0)
				return (-1);
		}
		else if (r->type == REDIR_INPUT)
		{
			if (handle_input_redirection(r, shell, last_in) < 0)
				return (-1);
		}
		else if (r->type == REDIR_OUTPUT || r->type == REDIR_APPEND)
		{
			if (handle_output_redirection(r, shell) < 0)
				return (-1);
		}
		r = r->next;
	}
	return (0);
}

int	apply_redirections(t_exec_unit *unit, t_mini *shell)
{
	int	last_in;

	last_in = -1;
	if (apply_redir_list(unit->redirs, shell, &last_in) < 0)
		return (-1);
	if (last_in != -1 && last_in != STDIN_FILENO)
		close(last_in);
	return (0);
}
