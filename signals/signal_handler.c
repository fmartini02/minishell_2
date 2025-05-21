/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:55:51 by francema          #+#    #+#             */
/*   Updated: 2025/05/20 17:56:22 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Gestisce SIGINT(Ctrl+C), stampa una nuova riga e ripristina il prompt senza uscire dalla shell*/
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		sig_code = SIGINT;
		write (STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	/*else if (sig == SIGQUIT)
	{
		sig_code = SIGQUIT;
		write (STDOUT_FILENO, "Quit (core dumped)\n", 19);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}*/
}
