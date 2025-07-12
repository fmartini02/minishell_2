/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sig_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:54:34 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 14:16:10 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern volatile sig_atomic_t	g_sig_code;

/* Se NON interativa, segnali di default
Se interattiva, installa il tuo signal_handler,
ignora tutti i segnali tranne SIGKILL, SIGSTOP, SIGINT*/
void	setup_sig_handler(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	g_sig_code = 130;
	sigaction(SIGQUIT, &sa, NULL);
}
