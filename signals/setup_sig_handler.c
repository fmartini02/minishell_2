/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sig_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:54:34 by francema          #+#    #+#             */
/*   Updated: 2025/06/28 14:21:46 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Se NON interativa, segnali di default
Se interattiva, installa il tuo signal_handler,
ignora tutti i segnali tranne SIGKILL, SIGSTOP, SIGINT*/
void	setup_sig_handler(int is_interactive)
{
	struct sigaction sa;

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
		// Gestisce SIGINT (Ctrl+C) con il tuo handler
		sa.sa_handler = signal_handler;
		sigaction(SIGINT, &sa, NULL);

		// Ignora SIGQUIT (Ctrl+\)
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
}
