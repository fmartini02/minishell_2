/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_heredoc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:45:59 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/07 14:50:55 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sig_code;

void	write_ctrld(const char *delimiter)
{
	write(2, "minishell warning: here-document ", 34);
	write(2, "delimited by end-of-file (wanted `", 35);
	write(2, delimiter, strlen(delimiter));
	write(2, "')\n", 3);
}

void	heredoc_sigint_handler(int sig)
{
	char	c;

	c = '\n';
	(void)sig;
	g_sig_code = 130;
	ioctl(0, TIOCSTI, &c);
	write(1, "^C\n", 3);
	rl_on_new_line();
}

void	prepare_and_check_heredocs(t_ast_node *node, t_mini *shell)
{
	if (prepare_heredocs(node, shell) < 0 || g_sig_code == 130)
	{
		g_sig_code = 0;
		close_all_heredoc_fds(node);
		return ;
	}
}

int	sigaction_return(struct sigaction *old_sa, int ret_value)
{
	sigaction(SIGINT, old_sa, NULL);
	return (ret_value);
}
