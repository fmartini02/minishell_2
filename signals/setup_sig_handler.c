/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sig_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:54:34 by francema          #+#    #+#             */
/*   Updated: 2025/06/28 18:56:44 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern volatile sig_atomic_t g_sig_code;

/* Se NON interativa, segnali di default
Se interattiva, installa il tuo signal_handler,
ignora tutti i segnali tranne SIGKILL, SIGSTOP, SIGINT*/
void	setup_sig_handler(int is_interactive)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (!is_interactive)
	{
		sa.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
	{
		sa.sa_handler = signal_handler;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
}

/* 
void	setup_sig_handler(int is_interactive)
{
	struct sigaction sa;
	struct sigaction ignore_sa;
	int i;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (!is_interactive)
		sa.sa_handler = SIG_DFL;
	else
	{
		sa.sa_handler = signal_handler;
		sigaction(SIGQUIT, &sa, NULL);
		sigaction(SIGINT, &sa, NULL);
		i = -1;
		while(++i < _NSIG)
		{
			if (i == SIGKILL || i == SIGSTOP || i == SIGINT)
				continue;
			ft_memset(&ignore_sa, 0, sizeof(ignore_sa));
			ignore_sa.sa_handler = SIG_IGN;
			sigaction(i, &ignore_sa, NULL);
		}
	}
} */