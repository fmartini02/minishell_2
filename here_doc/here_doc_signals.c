/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 22:47:29 by francema          #+#    #+#             */
/*   Updated: 2025/07/15 14:34:12 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	g_sig_code = true;
	write(1, "^C\n", 3);
	ioctl(0, TIOCSTI, &c);
	rl_on_new_line();
}

int	sigaction_return(struct sigaction *old_sa, int ret_value)
{
	sigaction(SIGINT, old_sa, NULL);
	return (ret_value);
}

void	setup_heredoc_signals(struct sigaction *old_sa)
{
	struct sigaction	sa;

	g_sig_code = 0;
	sa.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, old_sa);
}
