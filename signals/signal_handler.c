/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:55:51 by francema          #+#    #+#             */
/*   Updated: 2025/06/28 14:27:03 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Gestisce SIGINT(Ctrl+C), stampa una nuova riga e ripristina il prompt senza uscire dalla shell*/
void	signal_handler(int sig)
{
	if (sig_code != -42)
		return ;
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "^C\n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
