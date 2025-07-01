/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:56:38 by francema          #+#    #+#             */
/*   Updated: 2025/07/01 17:03:58 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Gestisce la fine dell'input (utente preme ctrl+D),
libera la memoria ed esce*/
void	ctrl_d_case(t_mini *shell)
{
	write(1, "exit\n", 5);
	cleanup_shell(shell, 0);
}
